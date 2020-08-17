SPOOL \Users\december\Desktop\assignment0\solution3
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON 

ALTER TABLE Recording ADD visit_hotels VARCHAR(20);
ALTER TABLE Recording ADD visit_country VARCHAR(20);

UPDATE Recording SET visit_hotels='1', visit_country='USA' WHERE travellers_number='P48709210'
AND travellers_nationality='Chinese';

UPDATE Recording SET visit_hotels='1', visit_country='CHINA' WHERE travellers_number='P99992164'
AND travellers_nationality='Chinese';

UPDATE Recording SET visit_hotels='1', visit_country='CHINA' WHERE travellers_number='812215381'
AND travellers_nationality='Australian';



SPOOL OFF