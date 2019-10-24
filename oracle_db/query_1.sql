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
where maxs.total_sum = maxs.max_sum and monh_order >= 4
;
