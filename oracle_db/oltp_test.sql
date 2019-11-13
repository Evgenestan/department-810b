1)
SELECT * FROM sales_order;

2)
SELECT * FROM sales_order where ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY');

3)
SELECT * FROM sales_order where ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY') and ORDER_DATE <to_date('15-07-2016','DD-MM-YYYY');

4)
SELECT * FROM manager where MANAGER_FIRST_NAME = 'Henry';

5)
SELECT * FROM SALES_ORDER a, MANAGER b  where a.MANAGER_ID = b.MANAGER_ID and b.manager_first_name = 'Henry';

6)
SELECT distinct country FROM CITY;

7)
SELECT distinct country, region FROM CITY;

8)
SELECT country, count(CITY_NAME) as amount FROM CITY GROUP BY country;

9)
SELECT a.product_qty,b.order_date  from SALES_ORDER_LINE a, SALES_ORDER b where
a.sales_order_id = b.sales_order_id and b.order_date > to_date('01-01-2016','DD-MM-YYYY') and
b.order_date <to_date('30-01-2016','DD-MM-YYYY');

10)
SELECT region FROM CITY UNION SELECT country FROM CITY UNION SELECT city_name FROM CITY;

11)

SELECT * from manager,
(SELECT  sss.manager_id as unid ,
         sum(sss.product_price*sss.product_qty) as income
         FROM (
        SELECT a.manager_id, c.product_price, c.product_qty, b.order_date FROM  MANAGER a  LEFT OUTER JOIN SALES_ORDER b ON a.manager_id = b.manager_id
        LEFT OUTER JOIN SALES_ORDER_LINE c ON b.sales_order_id = c.sales_order_id
        ) sss
        where sss.ORDER_DATE >= to_date('01-01-2016','DD-MM-YYYY')
            and sss.ORDER_DATE <= to_date('31-01-2016','DD-MM-YYYY') group by sss.manager_id
) j where j.income = (
        select
         max(sum(c.product_price*c.product_qty)) as income
         FROM  MANAGER a  LEFT OUTER JOIN SALES_ORDER b ON a.manager_id = b.manager_id
        LEFT OUTER JOIN SALES_ORDER_LINE c ON b.sales_order_id = c.sales_order_id
        where b.ORDER_DATE >= to_date('01-01-2016','DD-MM-YYYY')
            and b.ORDER_DATE <= to_date('31-01-2016','DD-MM-YYYY') group by a.manager_id
) and manager.manager_id = j.unid;





