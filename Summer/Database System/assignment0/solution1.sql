SPOOL \Users\december\Desktop\assignment0\solution1
SET ECHO ON
SET FEEDBACK ON
SET LINESIZE 100
SET PAGESIZE 200
SET SERVEROUTPUT ON

CREATE TABLE Traveller
(
passport_number VARCHAR(20) NOT NULL,
nationality VARCHAR(20) NOT NULL,
first_name VARCHAR(20),
last_name VARCHAR(20),
birth_date VARCHAR(20),
CONSTRAINT travel_id PRIMARY KEY (passport_number,nationality)
);



CREATE TABLE Hotel
(
hotel_name VARCHAR(100) NOT NULL,
country VARCHAR(20) NOT NULL,
city VARCHAR(20) NOT NULL,
street_name VARCHAR(100) NOT NULL,
building_number VARCHAR(20) NOT NULL,
possessed_stars VARCHAR(20),
CONSTRAINT hotel_id PRIMARY KEY (hotel_name, city),
CONSTRAINT hotel_location UNIQUE(country, city, street_name, building_number)
);

CREATE TABLE Recording
(
departue_date VARCHAR(20),
arrival_date VARCHAR(20),
visit_time VARCHAR(100),
travellers_number VARCHAR(20),
travellers_nationality VARCHAR(20),
hotels_name VARCHAR(100),
hotels_city VARCHAR(20),
PRIMARY KEY (travellers_number, travellers_nationality)
);

SPOOL OFF
