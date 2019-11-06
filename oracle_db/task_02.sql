-- query_01

with sales as(
select round(months_between(sale_date,to_date('01.09.2013','dd.mm.yy'))) as monh_order, manager_id, sum(sale_amount) sale_sum 
from v_fact_sale
where  to_date(sale_date,'DD.MM.YY')  >= to_date('01.10.2013','DD.MM.YY') AND to_date(sale_date,'DD.MM.YY') < to_date('01.12.2014','DD.MM.YY') 
group by round(months_between(sale_date,to_date('01.09.2013','dd.mm.yy'))),manager_id),
total_sums as 
(
select sales.monh_order,manager_id ,
sum(sales.sale_sum) over (partition by sales.manager_id order by sales.monh_order range between 3 preceding and current row) total_sum 
from sales),
max_sums as (select total_sums.manager_id,total_sums.monh_order,total_sums.total_sum,
max(total_sums.total_sum) over (partition by total_sums.monh_order) max_sum
from total_sums) 
select mngs.manager_id,mngs.manager_first_name,mngs.manager_last_name,(maxs.max_sum * 0.05) premia
from max_sums maxs join manager mngs on maxs.manager_id = mngs.manager_id
where maxs.total_sum = maxs.max_sum and monh_order >= 4;

--query_02

with sum_officies as (select office_id, city_name, extract(YEAR from sale_date) year,country, sum(sale_amount) sum_sales
                      from V_FACT_SALE
                      where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2013','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2015','DD.MM.YY')
                      group by office_id,extract(YEAR from sale_date), country, city_name),
sum_officies_by_year as( select sum_officies.office_id, sum_officies.city_name, sum_officies.year, sum_officies.country, sum_officies.sum_sales, sum(sum_officies.sum_sales) over (partition by year) total_sum
                         from sum_officies)
select office_id, city_name, year, country, sum_sales/total_sum relative_amount from sum_officies_by_year
order by relative_amount desc;

--query_03

with months as (    select product_id, product_name, sum(sale_amount) month_prod_qty,  trunc(MONTHS_BETWEEN(sale_date,to_date('01.12.13','DD.MM.YY'))) month_order
                    from V_FACT_SALE
                    where to_date(sale_date,'DD.MM.YY') >= to_date('01.12.2013','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.07.2014','DD.MM.YY')
                    group by product_id,  trunc(MONTHS_BETWEEN(sale_date,to_date('01.12.13','DD.MM.YY'))), product_name
                    order by product_id),
products as (   select months.product_id, months.product_name, months.month_order, months.month_prod_qty, LAG(months.month_prod_qty) over (partition by months.product_id order by months.month_order) as prev_qty
                from months
                order by product_id, month_order)
select product_id, product_name, max(month_prod_qty/prev_qty) as speed_size
from products
where prev_qty is not  null
group by product_name, product_id
order by speed_size desc;