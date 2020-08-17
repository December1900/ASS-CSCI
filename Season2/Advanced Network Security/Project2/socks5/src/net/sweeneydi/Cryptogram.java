package net.sweeneydi;

import javax.crypto.*;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.SecretKeySpec;
import java.security.*;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.util.Base64;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Cryptogram {

    private Cipher mCipher;
    private SecretKey mSecretKey;
    private SecureRandom random;
    private GCMParameterSpec mGCMParameterSpec;

    public Cryptogram(String pw) {

        String password = pw;

        try {
            if (password == null || password.isEmpty()) {
                KeyGenerator keyGen = KeyGenerator.getInstance("AES");
                // choose aes-256
                keyGen.init(256);
                password = Base64.getEncoder().encodeToString(keyGen.generateKey().getEncoded());
            }

            final byte[] salt = new byte[64];
            random = SecureRandom.getInstanceStrong();
            random.nextBytes(salt);

            // use PKDF2 to derive the secret K
            SecretKeyFactory secretKeyFactory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA512");
            KeySpec passwordBasedEncryptionKeySpec = new PBEKeySpec(password.toCharArray(), salt, 10000, 256);
            SecretKey secretKeyFromPBKDF2 = secretKeyFactory.generateSecret(passwordBasedEncryptionKeySpec);
            this.mSecretKey = new SecretKeySpec(secretKeyFromPBKDF2.getEncoded(), "AES");
            this.mCipher = Cipher.getInstance("AES/GCM/NoPadding");


        } catch (NoSuchAlgorithmException | NoSuchPaddingException | InvalidParameterException | InvalidKeySpecException e) {
            Logger LOGGER = Logger.getLogger(Cryptogram.class.getName());
            LOGGER.log(Level.SEVERE, e.getLocalizedMessage());
            e.printStackTrace();
        }

    }

    public byte[] encrypt(byte[] data) throws BadPaddingException, IllegalBlockSizeException, InvalidAlgorithmParameterException, InvalidKeyException {
        byte[] nonce = new byte[32];
        random.nextBytes(nonce);
        mGCMParameterSpec = new GCMParameterSpec(16 * 8, nonce);
        mCipher.init(Cipher.ENCRYPT_MODE, mSecretKey, mGCMParameterSpec);
        return mCipher.doFinal(data);
    }

    public byte[] decrypt(byte[] data) throws InvalidAlgorithmParameterException, InvalidKeyException, BadPaddingException, IllegalBlockSizeException {
        mCipher.init(Cipher.DECRYPT_MODE, mSecretKey, mGCMParameterSpec);
        return mCipher.doFinal(data);
    }

}
