SELECT AVG(energy) FROM songs JOIN artists ON artists.id = songs.artist_id WHERE artists.name = 'Drake';
-- or could say
-- SELECT AVG(energy) FROM (SELECT songs.energy FROM songs JOIN artists ON artists.id = songs.artist_id WHERE artists.name = 'Drake');
--In 7.sql, write a SQL query that returns the average energy of songs that are by Drake