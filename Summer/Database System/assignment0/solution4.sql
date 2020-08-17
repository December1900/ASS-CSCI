SPOOL \Users\december\Desktop\assignment0\solution5
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON 

TRUNCATE TABLE hotel;
TRUNCATE TABLE recording;

ALTER TABLE Hotel ADD visit_tnumber VARCHAR(20);

INSERT INTO Hotel VALUES('Orlando World Center Marriott', 'USA', 'Orlando', 'World Center Drive', '8701' , '5','2');

INSERT INTO Recording VALUES('2019-06-01','2019-06-02','1','P48709210','Chinese','Orlando World Center Marriott','Orlando','1','USA');
INSERT INTO Recording VALUES('2019-08-03','2019-08-10','1','P99992164', 'Chinese','Orlando World Center Marriott', 'Orlando','1','USA');





SPOOL OFF