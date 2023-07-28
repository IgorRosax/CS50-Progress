-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
.schema
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
*/


select * from crime_scene_reports where street= 'Humphrey Street' ;

select * from interviews where year = 2021 and month = 7 and day >= 28 order by year, month, day;


select t.name thief, l.activity park_activity, l.hour park_hour, l.minute park_minute, a.name Accomplice, c.duration call_duration,
fo.city flight_origin, fd.city flight_destination, f.year, f.month, f.day, f.hour, f.minute, bt.*

from phone_calls c 
inner join people t 
on c.caller = t.phone_number 
inner join people a 
on c.receiver = a.phone_number 

inner join bakery_security_logs l 
on t.license_plate = l.license_plate 
and c.year = l.year
and c.month = l.month
and c.day = l.day

inner join bank_accounts ba 
on t.id = ba.person_id
inner join atm_transactions bt 
on ba.account_number = bt.account_number 
and  c.year = bt.year
and c.month = bt.month
and c.day = bt.day

inner join flights f
on  c.year = f.year
and c.month = f.month
and c.day = f.day - 1
inner join airports fo
on f.origin_airport_id = fo.id
inner join airports fd
on f.destination_airport_id = fd.id
inner join passengers fp
on f.id = fp.flight_id
and t.passport_number = fp.passport_number

where c.year = 2021 and c.month = 7 and c.day = 28 and l.hour = 10 and l.minute between 15 and 25 
and c.duration < 60 
order by f.year, f.month, f.day, f.hour, f.minute
limit 1;


