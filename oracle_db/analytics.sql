/*  1) ������ ����� �������� ������ ������ � ������� 5% �� ����� ������ ���������, ������� �� ���������� 3 ������ ������ ������� �� ����� ������� �����
�������� �����, manager_id, manager_first_name, manager_last_name, ������ �� ������ � ������ �� ������� 2014 ����*/

---����� �� �������� � ������. 



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


/*  2) �������� ����� �������������� ���������� ������, ��������������� ������������� ������ ������ �� ������ � ������� ������� � 2013-2014 ��.
�������� ���, office_id, city_name, country, ������������� ����� ������ �� ������� ���
�����, ������� ������������� ���������� ������������� ����� � ������� ���� ��� ������ ����� ����� �������.*/

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

/*3. ��� ������������ �������, �������� ��������� �������� ����� ������ �� �������.
�������� ����������� ��� ��������� ������ ������ � ������� ������ � �����������.
�������� ������, ������� ��������������� �������� ������� ����� ����� ������ � ������� ������� ��������� 2014 ����.*/



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

/*  5. ������� ����� � ����� ������� �� 2014 ��� 10% �������� ������� ������� � 10% �������� ������� �������.
�������� product_id, product_name, total_sale_amount, percent*/
with t1 as (
select product_id, product_name, sum(sale_amount) total_sale_amount
from V_FACT_SALE
where to_date(sale_date,'DD.MM.YY') >= to_date('01.01.2014','DD.MM.YY') and to_date(sale_date,'DD.MM.YY') < to_date('01.01.2015','DD.MM.YY')
group by product_id, product_name
order by total_sale_amount desc),
t2 as (
select product_id, product_name, total_sale_amount,
sum(total_sale_amount) over() total_sum
--sum(sale_price) over() total_price_sum
from t1)
select product_id, product_name, total_sale_amount, total_sum, round(total_sale_amount/total_sum,2) percent
from t2
--where percent <=0.1 or percent >=0.9;




select * from V_FACT_SALE











