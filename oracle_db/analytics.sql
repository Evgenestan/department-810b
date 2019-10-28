/*  1) Каждый месяц компания выдает премию в размере 5% от суммы продаж менеджеру, который за предыдущие 3 месяца продал товаров на самую большую сумму
Выведите месяц, manager_id, manager_first_name, manager_last_name, премию за период с января по декабрь 2014 года*/

---сумма по менджеру и месяцу. 



with sales as(
select  manager_id, sum(sale_amount) sale_sum, trunc(MONTHS_BETWEEN(sale_date,to_date('01.09.13','DD.MM.YY'))) month_order, manager_first_name, manager_last_name
from V_FACT_SALE 
where to_date(sale_date,'DD.MM.YY') >= to_date('01.10.2013','DD.MM.YY') and  to_date(sale_date,'DD.MM.YY') < to_date('01.12.2014','DD.MM.YY')
group by  manager_id, trunc(MONTHS_BETWEEN(sale_date, to_date('01.09.13','DD.MM.YY'))), manager_first_name, manager_last_name ),
temp2 as(
select manager_id, 
sales.month_order,
sales.manager_first_name,
sales.manager_last_name,
sum(sales.sale_sum) over (partition by sales.manager_id order by sales.month_order RANGE BETWEEN  3  PRECEDING AND CURRENT ROW) total_sum
from sales),
t3 as(
select temp2.manager_id, temp2.month_order, temp2.total_sum, temp2.manager_first_name, temp2.manager_last_name,
MAX(temp2.total_sum) over (partition by temp2.month_order) final_sum
from temp2)
select t3.manager_id, t3.month_order, t3.total_sum, t3.final_sum, t3.manager_last_name, t3.manager_first_name, t3.final_sum*0.05 premia
from t3 
where t3.final_sum = t3.total_sum and t3.month_order>=4;


/*  2) Компания хочет оптимизировать количество офисов, проанализировав относительные объемы продаж по офисам в течение периода с 2013-2014 гг.
Выведите год, office_id, city_name, country, относительный объем продаж за текущий год
Офисы, которые демонстрируют наименьший относительной объем в течение двух лет скорее всего будут закрыты.*/

select * from V_FACT_SALE;



with t1 as(
select office_id,
city_name,
extract(YEAR from sale_date) year,
country,
sum(sale_amount) office_sales
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2013','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2014','DD.MM.YY')
group by office_id,extract(YEAR from sale_date), country, city_name),
t2 as(
select t1.office_id, 
t1.city_name, 
t1.year, 
t1.country, 
t1.office_sales,
sum(t1.office_sales) over () total_sum
from t1)
select office_id, city_name, year, country, office_sales/total_sum relative_amount from t2
order by relative_amount desc;

/*3. Для планирования закупок, компанию оценивает динамику роста продаж по товарам.
Динамика оценивается как отношение объема продаж в текущем месяце к предыдущему.
Выведите товары, которые демонстрировали наиболее высокие темпы роста продаж в течение первого полугодия 2014 года.*/



with t1 as 
(
select product_id, product_name, sum(sale_qty) month_prod_qty,  trunc(MONTHS_BETWEEN(sale_date,to_date('01.12.13','DD.MM.YY'))) month_order
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.12.2013','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.07.2014','DD.MM.YY')
group by product_id,  trunc(MONTHS_BETWEEN(sale_date,to_date('01.12.13','DD.MM.YY'))), product_name
order by product_id
),
t2 as (
select t1.product_id, t1.product_name, t1.month_order, t1.month_prod_qty, LAG(t1.month_prod_qty) over (partition by t1.product_id order by t1.month_order) as prev_qty
from t1
order by product_id, month_order)
select product_id, product_name, max(month_prod_qty/prev_qty) as speed_size
from t2
where prev_qty is not  null
group by product_name, product_id
order by speed_size desc
;

/*  5. Найдите вклад в общую прибыль за 2014 год 10% наиболее дорогих товаров и 10% наиболее дешевых товаров.
Выведите product_id, product_name, total_sale_amount, percent*/

with t0 as (
select product_id, product_name, sale_amount, AVG(sale_price) over(partition by product_id) av_sal
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2014','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2015','DD.MM.YY')
),
t1 as (
select product_id, product_name, sum(sale_amount) total_sale_amount, av_sal
from t0
group by product_id, product_name, av_sal
order by total_sale_amount desc),
t2 as (
select product_id, product_name, total_sale_amount, av_sal,
sum(total_sale_amount) over() total_sum,
sum(av_sal) over() total_av_sum
--sum(sale_price) over() total_price_sum
from t1),
t3 as(
select product_id,
product_name,
total_sum,
total_sale_amount,
round(av_sal 
/total_av_sum,2)*100 "total_impact%",
row_number () over (order by av_sal desc) top_sal,
av_sal,
total_av_sum,
count(*) over () count_num
from t2
order by av_sal desc)

select product_id,product_name, total_sale_amount, round(total_sale_amount/total_sum*100,2) percent
from t3
where top_sal <= round(0.1*count_num) or top_sal >= round(0.9*count_num);
--where rownum <= round(count(*)*0.1) or rownum >= round(count(*)*0.9)

  

 
select * from V_FACT_SALE;

 

/*6. Компания хочет премировать трех наиболее продуктивных (по объему продаж, конечно) менеджеров в каждой стране в 2014 году.
Выведите country, <список manager_last_name manager_first_name, разделенный запятыми> которым будет выплачена премия */

with t0 as (
select manager_id, manager_last_name, manager_first_name, country, sale_date, sale_qty,
SUM(sale_qty) over (partition by country,manager_id order by sale_qty) country_sale_qty
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2014','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2015','DD.MM.YY')
order by country ),
t1 as (
select  
distinct 
last_value(country_sale_qty ) over (partition by country, manager_id) manager_sum,
manager_id, manager_last_name, manager_first_name, country
from t0),
t2 as (select
manager_sum,
manager_id, manager_last_name, manager_first_name, country,
rank() over (partition by country order by manager_sum) rank_id
from t1)
select country, manager_last_name|| ' , ' ||manager_first_name name
from t2
where rank_id = 1 or rank_id = 2 or rank_id = 3;




/*7. Выведите самый дешевый и самый дорогой товар, проданный за каждый месяц в течение 2014 года.
cheapest_product_id, cheapest_product_name, expensive_product_id, expensive_product_name, month, cheapest_price, expensive_price*/


select * from V_FACT_SALE;

with t0 as (
select product_name,
product_id,
sale_price,
trunc(MONTHS_BETWEEN(sale_date,to_date('01.12.13','DD.MM.YY'))) month_order
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2014','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2015','DD.MM.YY')
 ),
 t1 as(
select 
product_id,
product_name,
month_order,
sale_price,
max (sale_price) over (partition by month_order) max_cost_prod,
min (sale_price) over (partition by month_order) min_cost_prod
from t0 )
select 
product_id,
product_name,
month_order,
sale_price,
max_cost_prod,
min_cost_prod,
rank() over (partition by month_order order by sale_price desc) rank_id
from t1
where max_cost_prod = sale_price or min_cost_prod = sale_price;



 
 






















