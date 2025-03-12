----------------
24th of February 2025
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


----------------
26th of February 2025
----------------
Before lunch:


Started to edit key_hook so that pressing W moves player up until released and S down.
<- rotates left and rotates right ->.

Added float p_y, p_x, p_d_y (player delta y), p_d_x and pa (player angle) to struct.


```
    void	key_hook(mlx_key_data_t keydata, void *param)
    {
    	t_cubed	*cubed;     


	    cubed = (t_cubed *)param   ;
    	if (keydata.key == MLX_KEY_ESCAPE)
		    terminate_free(cubed, 0, "Game ended\n");
    	if (mlx_is_key_down(cubed->mlx, MLX_KEY_W))
	    	cubed->p_y -= 0.1;
    	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_S))
    		subed->p_y += 0.1;
    	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_LEFT))
    		cubed->p_a -= 0.1;
    	else if (mlx_is_key_down(cubed->mlx, MLX_KEY_RIGHT))
    		cubed->p_a += 0.1;
    	if ((x != 0 || y != 0) && !move_player(cubed, x, y))
			return ;
    }
```

void buttons(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		pa -= 0.1; 
		if (pa < 0)
			pa += 2*PI;
		p_d_x = cos(pa)*5;
		p_d_y= sin(pa)*5;
	}
	if (key == 'd')
	{
		pa += 0.1; 
		if (pa > 2*PI)
			pa -= 2*PI;
		p_d_x = cos(pa)*5;
		p_d_y= sin(pa)*5;
	}
	if (key == 'w')
	{
		px += pdx;
		py += pdy;
	}
	if (key == 's')
	{
		px -= pdx;
		py -= pdy;
	}
}

----------------
27th of February 2025
----------------

Was a bad working day honestly, ran in circles and came back to 26th commit.

----------------
1st of March 2025
----------------

Before lunch:
- Moves our player : W goes up, S goes down, < and > change the direction.
- Draws the player with a trace, need to add draw map to every loop after lunch.

Last commit:
- Commented out in cub3d.c are different implementations for movement and draw_player using mlx_put_pixel. Right now its instead drawing and moving multiple points on walls, so totally not working properly. Will continue on monday (3.3.)

TO DO:
Make moving and rendering of minimap work on a basic level and pull from main and adjust bonus to use parsings output.

----------------
3rd of March 2025
----------------

- Player image is now moving to all directions.
- There's also a function (draw_player()) in comments where player is drawn using put_pixel and moved calling put_image_to_window. This seems too heavy compared to moving with instances.
- Rays are not drawn yet
- It doesn't succesfully understand the boundaries (walls), or it does, but it doesn't visualize it as we'd like to.

- Merged Helmi's work from main branch, starting to connect their parsing to my work tomorrow. Right now Helmi's main() is commented out.

----------------
4th of March 2025
----------------

- Synced bonus and main branches together so that Helmi's parsing and data structs align with
minimap handling and drawing. It makes and runs and shouldn't leak.
There is now:
- updated Makefile
- updated cub3d.h with additions to data structs, functions and libraries.

There are still some parts that need to be figured out together, for example:

How to best enhance enum e_type	*map's features when checking for valid player moves (will updating x and y make the player hit a wall).

- All the latest (today's) updates of parsing branch are not implemented, this is merged from main branch.

Remarks:
- I have free_2d_array() in my libft
- Is there a need to allocate +1 for map (not a char array)?


----------------
5th of March 2025
----------------

- Compared to main bonus has changes in moving_bonus.c. 
Trying to figure out how to do wall checks with current map that isn't 2D array.

But: If in index y = 3 and x = 3 an obstacle (WALL) exists, that means:

	(x,3) == WALL, but the wall takes up the whole tile/index.
	
	So also y = 2,000001 == WALL AND 2,99999999999 == WALL.
	
	(3,y) == WALL, but the wall takes up the whole tile/index.

	So also x = 3,000001 == WALL AND 3,99999999999 == WALL.

I'll continue on this thought tomorrow, but checking x and checking y obstacles is slightly different

----------------
6th of March 2025
----------------
Start of the day:

This morning I've drawn a fusion of a coordinate system and map (as a 2D array although our parsing handles map 1D).
Checking x and checking y obstacles is slightly different depending on the direction (map->player.angle) you're approaching from.

I'm not sure if I'm on the right track or making this too hard, but this is my hypothesis:

When moving up (N) ergo: y_new < y_current && player.angle < PI (180°), it's enough to check if y_new != WALL.
When moving down (S) ergo: y_new > y_current && player.angle > PI (180°), we need to check if y_new + 1 != WALL.


When moving left (W) ergo: x_new < x_current && player.angle < PI/2 (90°) || player.angle > 3PI/2 (270°).
When moving right (E) ergo: x_new > x_current && PI/2 (90°) < player.angle 3PI/2 (270°), we need to check if x_new - 1 = WALL.

Remembering that if our player.angle reaches 2PI (360°), we will -= 2PI (360°) making it start again with 0.

Update:

We've finally managed to update function `int		get_index_of_rov_and_col(t_data *data, int x, int y, int forward)	`
to succefully detect upcoming map index based on the direction (angle) we are headed to, and whether we are moving forward or backwards.
This means we can now detect if we are going to hit a wall or now, with the exception of quoins (outward corners).

- To do: Now we can move and detect walls when pressing W and S (Forward and back) with rotation, but need to also update movement to left and right.

- Started working on that, probably need another variables for delta_x and delta_y. We now have player.d_x and player.d_y which are based on forward and back movement:
	`data->player.d_x = cos(data->player.angle) * move_speed;`
	`data->player.d_y = sin(data->player.angle) * move_speed;`

but for left and right movement it goes:

	`data->player.d_x = cos(data->player.angle + PI / 2) * move_speed;`
	`data->player.d_y = sin(data->player.angle + PI / 2) * move_speed;`

Will continue working with this tomorrow.

----------------
7th of March 2025
----------------

- Morning brain is amazing, in just 15 mins I managed to get our player move 
with A and D keys to left and right in 90 deg difference compared to back and front.

- I managed it now by locally calculating new delta_x's and delta_y's, but will probably add 
new variables to struct once I know how to name them.

- created a separate function turn_player(t_data *data) for updating players angle and player.delta_x and player.delta_y instead of
handling it in the moving functions.

- Added enum dir_type struct for moving direction, enums = "FORWARD, REVERSE, LEFT, RIGHT".

----------------
8th of March 2025
----------------

- Floor and ceiling are drawn, now we start to build the raycaster logic together.

----------------
12th of March 2025
----------------

- What a day, we got raycasting to work on the minimap (2D raycasting),
- We started to implement logic for drawing 3D world with one color. It's fisheyed (Euclidean) now and only works with player == N.