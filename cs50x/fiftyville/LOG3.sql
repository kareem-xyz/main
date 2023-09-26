-- GET FLIGHT
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour, minute ASC LIMIT 1;
-- FLight id = 36
SELECT *
  FROM people
  INNER JOIN bank_accounts AS bank
  ON bank.person_id = people.id
 WHERE license_plate IN
    (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute >= 15
        AND minute <= 25
        AND activity = 'exit'
    )
   AND passport_number IN
 (
    SELECT passport_number
      FROM passengers
     WHERE flight_id = 36
 )
   AND phone_number IN
 (
    SELECT caller
    FROM phone_calls
    WHERE duration > 60
    AND year = 2021
    AND month = 7
    AND day = 28
 )
  AND bank.account_number IN
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
  --RESULT: Theif's Name is Bruce
-- Acomplice
  SELECT *
  FROM people
  WHERE phone_number IN
  (
    SELECT receiver
    FROM phone_calls
    WHERE caller = '(367) 555-5533'
    AND duration < 60
    AND year = 2021
    AND month = 7
    AND day = 28
  )
-- Acomplice's name is Robin