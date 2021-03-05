-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE (year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street"); --Get description
SELECT name, transcript FROM interviews WHERE (year = 2020 AND month = 7 AND day = 28); --Get Interviews


SELECT name, passport_number FROM people WHERE phone_number IN
(
SELECT caller FROM phone_calls WHERE
(year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(
SELECT phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE (year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
AND license_plate IN(SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25 AND activity = "exit"))
))
UNION
SELECT receiver FROM phone_calls WHERE
(year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(
SELECT phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE (year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
AND license_plate IN(SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25 AND activity = "exit"))
))); --Get Caller, Receiver details from phone numbers


SELECT city FROM airports WHERE
id = (
SELECT destination_airport_id FROM flights WHERE
(origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2020 AND month = 7 AND day = 29) ORDER BY hour, minute LIMIT 1
); --Get destination city from destination_city_id

SELECT seat, passport_number FROM passengers WHERE flight_id =
(
SELECT id FROM flights WHERE
(origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2020 AND month = 7 AND day = 29)
ORDER BY hour, minute LIMIT 1
) AND
passport_number IN
(
SELECT passport_number FROM people WHERE phone_number IN
(
SELECT caller FROM phone_calls WHERE
(year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(
SELECT phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE (year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
AND license_plate IN(SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25 AND activity = "exit"))
))
UNION
SELECT receiver FROM phone_calls WHERE
(year = 2020 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(
SELECT phone_number FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE (year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
AND license_plate IN(SELECT DISTINCT(license_plate) FROM courthouse_security_logs
WHERE (year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute <= 25 AND activity = "exit"))
)))
);  --Get seat, passport_number from flight_id










