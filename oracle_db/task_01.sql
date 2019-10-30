--1.Âûáðàòü âñå çàêàçû (SALES_ORDER)
SELECT * FROM sales_order;
--2.Âûáðàòü âñå çàêàçû, ââåäåííûå ïîñëå 1 ÿíâàðÿ 2016 ãîäà
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY');
--3.Âûáðàòü âñå çàêàçû, ââåäåííûå ïîñëå 1 ÿíâàðÿ 2016 ãîäà è äî 15 èþëÿ 2016 ãîäà
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY')
                            AND ORDER_DATE < to_date('15-07-2016','DD-MM-YYYY');
--4.Íàéòè ìåíåäæåðîâ ñ èìåíåì 'Henry' 
SELECT * FROM manager WHERE MANAGER_FIRST_NAME = 'Henry';
--5.Âûáðàòü âñå çàêàçû ìåíåäæåðîâ ñ èìåíåì Henry
SELECT * FROM manager, sales_order 
    WHERE manager.manager_id = sales_order.manager_id 
    AND MANAGER_FIRST_NAME = 'Henry';

--6.Âûáðàòü âñå óíèêàëüíûå ñòðàíû èç òàáëèöû CITY
SELECT DISTINCT country
    FROM CITY;
--7.Âûáðàòü âñå óíèêàëüíûå êîìáèíàöèè ñòðàíû è ðåãèîíà èç òàáëèöû CITY
SELECT DISTINCT country, region
    FROM CITY;
--8.Âûáðàòü âñå ñòðàíû èç òàáëèöû CITY ñ êîëè÷åñòâîì ãîðîäîâ â íèõ.
SELECT COUNT(region), country
    FROM CITY
    GROUP BY country;
--9.Âûáðàòü êîëè÷åñòâî òîâàðîâ (QTY), ïðîäàííîå ñ 1 ïî 30 ÿíâàðÿ 2016 ãîäà.
SELECT sale_qty 
    FROM mv_fact_sale 
    WHERE sale_date BETWEEN to_date('01-01-2016','DD-MM-YYYY') AND to_date('30-01-2016','DD-MM-YYYY');
--10.Âûáðàòü âñå óíèêàëüíûå íàçâàíèÿ ãîðîäîâ, ðåãèîíîâ è ñòðàí â îäíîé êîëîíêå
SELECT region FROM CITY
	UNION SELECT country FROM CITY
    UNION SELECT city_name FROM CITY;

--=================================
SELECT * FROM manager;        --===
SELECT * FROM mv_fact_sale;   --===
--=================================

--11.Âûâåñòè èìåíà è ôàìèëèè ìåíåäæåð(îâ), ïðîäàâøåãî òîâàðîâ â ÿíâàðå 2016 ãîäà íà íàèáîëüøóþ ñóììó.
with managers as (select manager_first_name,manager_last_name ,sum(product_price*product_qty) price
 from manager man join sales_order sale on man.manager_id = sale.manager_id
 join sales_order_line orderline on sale.sales_order_id = orderline.sales_order_id
 where order_date >= to_date('01/01/2016','DD.MM.YYYY') 
       AND order_date <= to_date('31/01/2016','DD.MM.YYYY')
 group by man.manager_id,manager_first_name,manager_last_name)
select manager_first_name,manager_last_name
from (select max(price) max_price from managers) maximum, managers
where managers.price = maximum.max_price;
