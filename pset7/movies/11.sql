SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN ratings ON stars.movie_id = ratings.movie_id
JOIN movies ON ratings.movie_id = movies.id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;
