def is_prime(n):
    if n == 1:
        return False
    i = 2
    while i * i <= n:
        if n % i == 0:
            return False
        i += 1

    return True


for x in range(1, 11):
    print('%d: %s' % (x, is_prime(x)))

print('%d: %s' % (10000000, is_prime(1000000000)))

print('%d: %s' % (10000005, is_prime(1000000007)))
