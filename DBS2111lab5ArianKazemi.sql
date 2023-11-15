-- ***********************
-- Name: AJAYI MICHAEL 
-- ID: 112462221
-- Date: 31-MAY-2023
-- Purpose: assignment 01 DBS211
-- ***********************

---QUESTION 1---
--1. Display employee number, employee full name, 
--phone, extension, city, manager ID, and manager name for employees who do not report to a manager. 
---(See the following output)Sort the result based on the city and the employee number.

SELECT a.employeenumber as "Employee Number",CONCAT(CONCAT(a.lastname,' '),a.firstname) as "Employee Name",b.phone as "Phone",
a.extension as "Extension",b.city as "City",
CASE when a.reportsto is null then 'Unknown' end as "Manager ID",CASE when a.reportsto is null then 'Unknown' end as "Manager Name"
FROM employees a 
LEFT JOIN offices b on a.officecode= b.officecode
WHERE a.reportsto is null  
ORDER BY b.city,a.employeenumber;



----QUESTION 2---
-- 2. Display employee number, employee full name, phone, 
--extension, and city for employees who work in NYC, Tokyo, 
--and Paris. Sort the result based on the city and the employeenumber      


SELECT a.employeenumber,CONCAT(CONCAT(a.firstname,' '),a.lastname) as "Employee Name",b.phone as "Phone",a.extension as "Extension",b.city as "City"
FROM employees a 
LEFT JOIN offices b on a.officecode= b.officecode
WHERE lower(city) in ('nyc', 'tokyo','paris')
ORDER BY city, employeenumber;



---QUESTION 3---
--3. Modify the query in Question 2 to display the manager ID and the manager name for theemployees returned by the previous query.
--Sort the result based on the city and theemployee number

SELECT a.employeenumber as "Employee Number",
       CONCAT(CONCAT(a.lastname, ', '), a.firstname) as "Employee Name",
       b.phone as "Phone",
       a.extension as "Extension",
       b.city as "City",
       a.reportsto as "Manager ID",
       CONCAT(CONCAT(m.firstname, ' '), m.lastname) as "Manager Name"
FROM employees a
LEFT JOIN offices b ON a.officecode = b.officecode
LEFT JOIN employees m ON a.reportsto = m.employeenumber
WHERE lower(b.city) IN ('nyc', 'tokyo', 'paris')
ORDER BY b.city, a.employeenumber;


---QUESTION 4--
--4. For all managers, display manager ID, manager name, country, 
---and the person who themanager reports to. See the following output. Sort the result according to the manager ID

--select a.employeenumber as "Manager ID",CONCAT(CONCAT(a.firstname, ' '), a.lastname) as "Manager Name", b.country,
--CASE when a.reportsto is not null then CONCAT(CONCAT('Reports to',' '), a.firstname) else 'Does not report to anyone' end
--as "Reports To"
--FROM employees a
--LEFT JOIN offices b ON a.officecode = b.officecode
---where a.employeenumber in (1002,1056,1088,1102,1143,1621)
---ORDER BY a.employeenumber;

SELECT a.employeenumber as "Manager ID",
       CONCAT(CONCAT(a.firstname, ' '), a.lastname) as "Manager Name",
       b.country,
       CASE WHEN a.reportsto IS NOT NULL THEN  CONCAT(CONCAT(CONCAT(CONCAT(CONCAT(CONCAT('Reports to', ' '),c.firstname), ' '), c.lastname),' ' ),c.JOBTITLE)
            ELSE 'Does not report to anyone'
       END as "Reports To"
FROM employees a
LEFT JOIN offices b ON a.officecode = b.officecode
LEFT JOIN employees c ON a.reportsto = c.employeenumber
ORDER BY a.employeenumber;



----QUESTION 5------
--The vendor 'Exoto Designs' offers a discount on some particular products. 
--The customerswho purchased products with quantity higher than 55 from this vendor are eligible toreceive the discount. 
--They will get 10% discount to purchase the same products they havepurchased with high quantity (> 55).
--Use the msrp column in the product table as the old price and calculate the new price usingthis column.
--In your report, display customernumber, customername, productcode, oldprice, and the new price

SELECT
    c.customernumber,
    c.customername,
    p.productcode,
    p.msrp as old_price,
    round(p.msrp * 0.9,2) as "New_price"
FROM
    customers c
    JOIN orders o ON c.customernumber = o.customernumber
    JOIN orderdetails oi ON o.ordernumber = oi.ordernumber
    JOIN products p ON oi.productcode = p.productcode
WHERE
p.productvendor = 'Exoto Designs'
    AND oi.quantityordered > 55
    ORDER BY c.customernumber asc;
    
    -------QUESTION 6------
    --Find the maximum value of priceeach for the product with productcode = 'S10_1678'.
    --Your query will return the same result as the following query:
    
SELECT MAX(od1.priceeach) as "Maximum Price"
FROM orderdetails od1
JOIN orderdetails od2 ON od1.productcode = od2.productcode
WHERE od1.productcode = 'S10_1678';


