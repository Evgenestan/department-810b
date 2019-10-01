--1.Выбрать все заказы (SALES_ORDER)
SELECT * FROM sales_order;
--2.Выбрать все заказы, введенные после 1 января 2016 года
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY');
--3.Выбрать все заказы, введенные после 1 января 2016 года и до 15 июля 2016 года
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY')
                            AND ORDER_DATE < to_date('15-07-2016','DD-MM-YYYY');
--4.Найти менеджеров с именем 'Henry' 
SELECT * FROM manager WHERE MANAGER_FIRST_NAME = 'Henry';
--5.Выбрать все заказы менеджеров с именем Henry
SELECT * FROM manager, sales_order 
    WHERE manager.manager_id = sales_order.manager_id 
    AND MANAGER_FIRST_NAME = 'Henry';

--6.Выбрать все уникальные страны из таблицы CITY
SELECT DISTINCT country
    FROM CITY;
--7.Выбрать все уникальные комбинации страны и региона из таблицы CITY
SELECT DISTINCT country, region
    FROM CITY;
--8.Выбрать все страны из таблицы CITY с количеством городов в них.
SELECT COUNT(region), country
    FROM CITY
    GROUP BY country;
--9.Выбрать количество товаров (QTY), проданное с 1 по 30 января 2016 года.
SELECT sale_qty 
    FROM mv_fact_sale 
    WHERE sale_date BETWEEN to_date('01-01-2016','DD-MM-YYYY') AND to_date('30-01-2016','DD-MM-YYYY');
--10.Выбрать все уникальные названия городов, регионов и стран в одной колонке
SELECT region FROM CITY
	UNION SELECT country FROM CITY
    UNION SELECT city_name FROM CITY;

--=================================
SELECT * FROM manager;        --===
SELECT * FROM mv_fact_sale;   --===
--=================================

--11.Вывести имена и фамилии менеджер(ов), продавшего товаров в январе 2016 года на наибольшую сумму.
SELECT manager_first_name, manager_last_name FROM manager;
    where 
