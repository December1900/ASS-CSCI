SPOOL \Users\december\Desktop\assignment0\solution2
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON 

INSERT INTO Traveller VALUES('P48709210', 'Chinese', 'Biao', 'GUO', '19910101');
INSERT INTO Traveller VALUES('P99992164', 'Chinese', 'Jun', 'LIU', '1998-02-03');
INSERT INTO Traveller VALUES('812215381', 'Australian', 'Eric', 'James', '1995-08-06');

INSERT INTO Hotel VALUES('Orlando World Center Marriott', 'USA', 'Orlando', 'World Center Drive', '8701' , '5');
INSERT INTO Hotel VALUES('Courtyard by Marriott', 'CHINA', 'Hong Kong', 'Ping Street, Shatin, N.T.', '1' ,'5');
INSERT INTO Hotel VALUES('City Garden Hotel','CHINA', 'Hong Kong', 'City Garden Road, North Point', '9','4');

INSERT INTO Recording VALUES('2019-06-01','2019-06-02','1','P48709210','Chinese','Courtyard by Marriott','Hong Kong');
INSERT INTO Recording VALUES('2019-08-03','2019-08-10','1','P99992164', 'Chinese','Orlando World Center Marriott', 'Orlando');
INSERT INTO Recording VALUES('2020-01-01','2020-01-03','1','812215381', 'Australian','Courtyard by Marriott','Hong Kong');

SPOOL OFF
