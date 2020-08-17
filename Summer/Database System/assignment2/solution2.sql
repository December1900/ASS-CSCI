SPOOL \Users\december\Desktop\assignment2\solution2
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON

CREATE OR REPLACE PROCEDURE INSERT_ORDER_DETAIL
(order_ids order_detail.order_id%TYPE,
product_names order_detail.product_name%TYPE,
unit_prices order_detail.unit_price%TYPE,
quantitys order_detail.quantity%TYPE,
discounts order_detail.discount%TYPE) IS
product_discontinued PRODUCT.DISCONTINUED%TYPE;
begin
select DISCONTINUED
into product_discontinued
from PRODUCT
where PRODUCT_NAME=product_names and rownum=1;
IF product_discontinued='N' THEN
dbms_output.put_line('Not allowed to insert the discontinued products');
ELSE 
INSERT INTO ORDER_DETAIL VALUES(order_ids,product_names,unit_prices,quantitys,discounts);
dbms_output.put_line('Successfully Insert');
END IF;
COMMIT;
END INSERT_ORDER_DETAIL;
/

EXECUTE INSERT_ORDER_DETAIL(331, 'Tourtiere', 7.45, 50,0);

EXECUTE INSERT_ORDER_DETAIL(350, 'Rossle Sauerkraut', 45.6, 38,0.05)





SPOOL OFF