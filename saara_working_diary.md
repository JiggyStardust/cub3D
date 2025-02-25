----------------
th of February 2025
----------------
- Continued the research about the raycasting part. Sources so far: https://lodev.org/cgtutor/raycasting.html and https://www.youtube.com/watch?v=gYRrGTC7GtA
- Doesn't run atm, a super basicc minimap is work in progress (trying to use my so_long as much as possible).

----------------
25th of February 2025
----------------
- This working branch (currently named: bonus) compiles and runs now
- It opens a very basic minimap, but handles movements like so_long, which means:
    - No rays are drawn our of the player yet
    - No rotation or subtle movements of the player implemented -> moves one tile at a time

To do:
- I'm still going to invest a little bit of my time for the minimap handling, since it's going to help me with getting familiar with mlx42 (minilibx) and
basic "2d Math". It also helps the parsing: this way we know what info is needed for the execution/raycasting.
- Would be cool if the final minimap was concentrated/zoomed image, which moves along with the player. No limitation to the map needed in that case.
