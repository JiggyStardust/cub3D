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