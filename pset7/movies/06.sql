SELECT AVG(rating) FROM movies
JOIN ratings on ratings.movie_id = movies.id
WHERE year = 2012;
