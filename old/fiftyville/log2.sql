/*
-Keep a log of any SQL queries you execute as you solve the mystery.
-GET THEIF SUSPECTS BY PLATE, NUMBER, ATM, AND FLIGHT
-GET ACOM SUSPECTA DATA BY NUMBER, FLIGHT. receiver in calls from theifs lists.
FIND POSSIBLE SUSPECTS BY COMPARING CALLERS ID AND RECEIVERS ID AGAINST SUSPECTS
*/

----------First: Get ID of crime report from crime_scene_reports
SELECT id FROM crime_scene_reports WHERE (year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street' AND description LIKE '%duck%')
-- RESULT : ID = 295

----------Second: GET INTERVIEWS DATA
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE '%thief%' OR '%bakery%' OR '%theft%'
--2.2 DATA                                                                                                                  |
--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within *TEN MINUTES* of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for *CARS* that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the *ATM* on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they *CALLED* someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the *PERSON* on the other end of the phone to *PURCHASE* the *FLIGHT TI*. |

--Conculsion: Look up The following:
--a. Theif's Car left parking lot after about ten minutes.
--b. Thief withdrew money from ATM at LEGGET street, in the morning of theft.
--c. Thief Called ACOMPLICE, at end of theft. DURATION less than minute, CONTENT purchase earliest flight ticket tomoroww(29/7), ACOMPLICE purchases for both people.

---------------------------SUSPECTS BY CLUES(INTERVIEWS DATA)

----------------A. THEIF SUSPECTS BY LICENSE PLATES

-----A.1 Get All License Plates data (Could potentially know time of theft)
SELECT *
FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit'

-----A.FINAL: (List of people's data BY license plates)
SELECT id
FROM people
WHERE license_plate IN
(
    SELECT license_plate
      FROM bakery_security_logs
     WHERE year = 2021
     AND month = 7
     AND day = 28
     AND activity = 'exit'
)

-----A.RESULT : Too long to write, USE A.FINAL.


---------------B. THEIF SUSPECTS BY ATM TRANSACTIONS

----B.1 Get All Atm withdrawl Transactions data (according to interview's data)
SELECT *
FROM atm_transactions
WHERE
(
        year = 2021
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
)

-----B.FINAL (List of peoples' data by atm_withdrawls)
SELECT person_id
FROM bank_accounts
WHERE account_number IN
(
    SELECT account_number
      FROM atm_transactions
     WHERE
    (
            year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
)

-----B.RESULT
-- IDS = (686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727 )


---------------C. BOTH SUSPECTS BY CALLS

-----C.1 Get all calls data on day.
SELECT *
FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60

-----C.2.1 CALLERS DATA (List of callers data by calls)
SELECT id
  FROM people
 WHERE phone_number IN
(
    SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)

-----C.2.2 RECEIVERS IDs (List of receiver's data by calls)
SELECT id
  FROM people
 WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
/*
-----C.3 BOTH CALLER and RECEIVER's NAMES ONLY (USEFUL FOR CHECKING ID's)
SELECT callers.name, receivers.name
FROM phone_calls
INNER JOIN
(
    SELECT name, phone_number
    FROM people
    WHERE phone_number IN
    (
        SELECT caller
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    )
)
AS callers
ON phone_calls.caller = callers.phone_number
INNER JOIN
(
    SELECT name, phone_number
    FROM people
    WHERE phone_number IN
    (
        SELECT receiver
        FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    )
)
AS receivers
ON phone_calls.receiver = receivers.phone_number
WHERE
(
        year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
)
-----Result of C.3
--    | (130) 555-0289 | (996) 555-8899 | Sofia   | Jack       |
--    | (499) 555-9472 | (892) 555-8872 | Kelsey  | Larry      |
--    | (367) 555-5533 | (375) 555-8161 | Bruce   | Robin      |
--    | (499) 555-9472 | (717) 555-1342 | Kelsey  | Melissa    |
--    | (286) 555-6063 | (676) 555-6554 | Taylor  | James      |
--    | (770) 555-1861 | (725) 555-3243 | Diana   | Philip     |
--    | (031) 555-6622 | (910) 555-3251 | Carina  | Jacqueline |
--    | (826) 555-1652 | (066) 555-9701 | Kenny   | Doris      |
--    | (338) 555-6650 | (704) 555-2131 | Benista | Anna
*/
-----C.FINAL (List Of IDs)
-----Callers
SELECT id
FROM people
WHERE phone_number IN
(
    SELECT caller
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)

-----RECEIVERS
SELECT id
FROM people
WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)

-----C.RESULT ID's FOR CALLERs AND RECEIVERS
-----CALLERS = (395717, 398010, 438727, 449774, 514354, 560886, 686048, 907148)
-----RECEIVERS = (250277, 251693, 484375, 567218, 626361, 712712, 847116, 864400, 953679)


---------------D. SUSPECTS BY FLIGHT
-----D.1 All suspected flights on 29th
SELECT *
  FROM flights
 WHERE origin_airport_id = 8
   AND year  = 2021
   AND month = 7
   AND day   = 29

-----D.2 ID OF FIFTYVILLE AIRPORT = 8
SELECT id FROM airports WHERE city = 'Fiftyville'

-----D.1 ID's of All people in Flights on 29th
SELECT id
  FROM people
 WHERE phone_number NOT NULL
   AND passport_number IN
       (
        SELECT passport_number
          FROM passengers
         WHERE flight_id IN
           (
            SELECT id
              FROM flights
             WHERE origin_airport_id = 8
               AND year  = 2021
               AND month = 7
               AND day   = 29
           )
       )

---------------------------- E.THEIF SUSPECTS:
--Combining lists of suspects BY 4 Lists
-- BY license
--Results of A : Too long to write
SELECT id
FROM people
WHERE license_plate IN
(
    SELECT id
      FROM people
     WHERE license_plate IN
    (
        SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit'
    )
)

--BY ATM
RESULT OF B: WITHDRAWERS ID = (686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727 )


--BY Callers numbers
Results OF C: CALLERS ID = (395717, 398010, 438727, 449774, 514354, 560886, 686048, 907148)

--BY Passengers on flights
--RESULTS OF D: Too long to write
SELECT id
  FROM people
 WHERE phone_number NOT NULL
   AND passport_number IN
       (
           SELECT passport_number
             FROM passengers
            WHERE flight_id IN
           (
                SELECT id
                  FROM flights
                 WHERE origin_airport_id = 8
                   AND year  = 2021
                   AND month = 7
                   AND day   = 29
            )
        )
--------------------------------------------------
-------------- ALL THEIF SUSPECTS ----------------
SELECT *
  FROM people
 WHERE --id IN -- ATM
       --(686048, 514354, 458378, 395717, 396669, 467400, 449774, 438727)
   --AND
   id IN -- Callers
       (395717, 398010, 438727, 449774, 514354, 560886, 686048, 907148)
   AND id IN -- license_plates
       (
            SELECT id
              FROM people
             WHERE license_plate IN
            (   SELECT license_plate
                  FROM
                (
                    SELECT *
                      FROM bakery_security_logs
                     WHERE year = 2021 AND month = 7 AND day = 28 AND activity = 'exit'
                )
            )
        )
    AND id IN -- Flights
        (
            SELECT id
              FROM people
             WHERE phone_number NOT NULL
               AND passport_number IN
                   (
                       SELECT passport_number
                         FROM passengers
                        WHERE flight_id IN
                              (
                                  SELECT id
                                    FROM flights
                                   WHERE origin_airport_id = 8
                                     AND year  = 2021
                                     AND month = 7
                                     AND day   = 29
                               )
                    )
            )
/* RESULTS : Final SUPECTS THEIFS ID's = (449774, 514354, 686048)
add ( by discarding atm's) =  (398010, 560886)
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+

| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
*/



----------------------------F. ACOMM SUSPECTS
--Containing Lists of suspects by 2 lists : Number, flights
-- BY FLIGHTS
SELECT id
  FROM people
 WHERE phone_number NOT NULL
   AND passport_number IN
       (
           SELECT passport_number
             FROM passengers
             WHERE flight_id IN
                  (
                      SELECT id
                        FROM flights
                       WHERE origin_airport_id = 8
                         AND year  = 2021
                         AND month = 7
                         AND day   = 29
                   )
        )

--BY Number (Extra field (theifs suspects called them))
SELECT id
  FROM people
 WHERE phone_number IN
(
    SELECT receiver
      FROM phone_calls
     WHERE year = 2021
       AND month = 7
       AND day = 28
       AND duration < 60
       AND caller IN
       (
           SELECT phone_number
             FROM people
            WHERE id IN (449774, 514354, 686048)
       )
)

--------------------------------------------------
-------------- ALL ACOMMP SUSPECTS----------------
SELECT *
  FROM people
 WHERE id IN
(
    SELECT id
      FROM people
     WHERE phone_number IN
     (
        SELECT receiver
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60
           AND caller IN
           (
            SELECT phone_number
              FROM people
             WHERE id IN
             (449774, 514354, 686048, 398010, 560886)
           )
      )
)
    AND id IN
(
      SELECT id
        FROM people
       WHERE phone_number NOT NULL
         AND passport_number IN
      (
             SELECT passport_number
               FROM passengers
              WHERE flight_id IN
             (
                    SELECT id
                    FROM flights
                    WHERE origin_airport_id = 8
                    AND year  = 2021
                    AND month = 7
                    AND day   = 29
             )
      )
)

POSSIBLE ACOMPS
/*
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 250277 | James  | (676) 555-6554 | 2438825627      | Q13SVG6       |
| 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |


ADD (extra)
| 251693 | Larry   | (892) 555-8872 | 2312901747      | O268ZZ0       |
| 626361 | Melissa | (717) 555-1342 | 7834357192      | NULL          |
*/
-- CONNECTING SUSPECTS
-- PEOPLE WHO CALLED ACOMP SUSPECTS
-- TAYLOR AND JAMES CANCELLED
-- DIANA AND PHILIP
-- BRUCE Is OUT
/*
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
+-----+----------------+----------------+------+-------+-----+----------+
*/
-- CONNECTING PEOPLE
SELECT *
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND caller IN
(
SELECT phone_number
    FROM people
    WHERE id IN
    (449774, 514354, 686048, 398010, 560886)
)
AND receiver IN
('(676) 555-6554', '(725) 555-3243', '(892) 555-8872', '(717) 555-1342')
--KELSEY AND MELISSA CANCELLED
-- KELSEY AND LARRY
SELECT *
  FROM passengers
 WHERE passport_number IN
       (8294398571, 2312901747)









