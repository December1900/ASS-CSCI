SPOOL \Users\december\Desktop\assignment0\solution5
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON 


SELECT possessed_stars from hotel where hotel_name = (select hotels_name from recording where travellers_number = 'P48709210'
AND travellers_nationality='Chinese');

SELECT possessed_stars from hotel where hotel_name = (select hotels_name from recording where travellers_number = 'P99992164'
AND travellers_nationality='Chinese');


SELECT hotel_name FROM hotel;

SELECT visit_tnumber FROM hotel WHERE hotel_name='City Garden Hotel';
SELECT visit_tnumber FROM hotel WHERE hotel_name='Courtyard by Marriott';
SELECT visit_tnumber FROM hotel WHERE hotel_name='Orlando World Center Marriott';

SELECT hotel_name FROM hotel WHERE visit_tnumber = '0';

SELECT last_name FROM traveller UNION SELECT hotel_name from hotel;

SPOOL OFF