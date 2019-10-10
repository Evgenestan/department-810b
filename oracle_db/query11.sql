with
(select manager_first_name,manager_last_name ,sum(product_price*product_qty) price
 from manager man join sales_order sale on man.manager_id = sale.manager_id
 join sales_order_line orderline on sale.sales_order_id = orderline.sales_order_id
 where order_date >= '01/01/2016' AND order_date <='31/01/2016'
 group by manager_first_name,manager_last_name) as managers
select manager_first_name,manager_last_name
from (select max(price) from managers) maximum, managers
where managers.price = maximum.price
