select s.name from songs s inner join artists a on s.artist_id = a.id where a.name = 'Post Malone';