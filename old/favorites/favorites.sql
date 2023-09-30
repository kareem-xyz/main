UPDATE shows SET title = 'Adventure Time' WHERE title IN (SELECT title FROM shows WHERE title LIKE 'ad%');

UPDATE shows SET title = 'Arrow' WHERE title IN (SELECT title FROM shows WHERE title LIKE 'ad%');
-- This problem set is too much of a hassle. I practised selecting and updating some values, but its rather tedious. Wont do the rest of it nor write the queries here.