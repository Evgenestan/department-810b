--1.������� ��� ������ (SALES_ORDER)
SELECT * FROM sales_order;
--2.������� ��� ������, ��������� ����� 1 ������ 2016 ����
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY');
--3.������� ��� ������, ��������� ����� 1 ������ 2016 ���� � �� 15 ���� 2016 ����
SELECT * FROM sales_order WHERE ORDER_DATE > to_date('01-01-2016','DD-MM-YYYY')
                            AND ORDER_DATE < to_date('15-07-2016','DD-MM-YYYY');
--4.����� ���������� � ������ 'Henry' 
SELECT * FROM manager WHERE MANAGER_FIRST_NAME = 'Henry';
--5.������� ��� ������ ���������� � ������ Henry
SELECT * FROM manager, sales_order 
    WHERE manager.manager_id = sales_order.manager_id 
    AND MANAGER_FIRST_NAME = 'Henry';

--6.������� ��� ���������� ������ �� ������� CITY
SELECT DISTINCT country
    FROM CITY;
--7.������� ��� ���������� ���������� ������ � ������� �� ������� CITY
SELECT DISTINCT country, region
    FROM CITY;
--8.������� ��� ������ �� ������� CITY � ����������� ������� � ���.
SELECT COUNT(region), country
    FROM CITY
    GROUP BY country;
--9.������� ���������� ������� (QTY), ��������� � 1 �� 30 ������ 2016 ����.
SELECT sale_qty 
    FROM mv_fact_sale 
    WHERE sale_date BETWEEN to_date('01-01-2016','DD-MM-YYYY') AND to_date('30-01-2016','DD-MM-YYYY');
--10.������� ��� ���������� �������� �������, �������� � ����� � ����� �������
SELECT region FROM CITY
	UNION SELECT country FROM CITY
    UNION SELECT city_name FROM CITY;

--=================================
SELECT * FROM manager;        --===
SELECT * FROM mv_fact_sale;   --===
--=================================

--11.������� ����� � ������� ��������(��), ���������� ������� � ������ 2016 ���� �� ���������� �����.
SELECT manager_first_name, manager_last_name FROM manager;
    where 
