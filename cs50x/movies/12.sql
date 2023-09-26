--In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
--Your query should output a table with a single column for the title of each movie.
--You may assume that there is only one person in the database with the name Johnny Depp.
--You may assume that there is only one person in the database with the name Helena Bonham Carter.
SELECT title FROM movies
    WHERE id IN
    (
        SELECT movie_id FROM
            (
                SELECT movie_id FROM stars
                WHERE person_id IN (SELECT id from people WHERE (name = 'Helena Bonham Carter' OR name = 'Johnny Depp'))
            )
        GROUP BY movie_id
        HAVING COUNT(movie_id) > 1
    )
    ORDER BY title ASC
;