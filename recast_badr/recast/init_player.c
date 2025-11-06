#include "../includes/cub3d.h"

#include "../includes/cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void move_player(t_game *game, double dx, double dy)
{
	double new_x;
	double new_y;
	double old_x;
	double old_y;
	int map_x;
	int map_y;

	old_x = game->player.ply_x;
	old_y = game->player.ply_y;
	new_x = old_x + dx;
	new_y = old_y + dy;

	// Check collision for X movement
	map_x = (int)(new_x / game->img.cell_size);
	map_y = (int)(old_y / game->img.cell_size);
	if (map_x >= 0 && map_x < 25 &&
		map_y >= 0 && map_y < 17 &&
		game->map[map_y][map_x] != '1')
	{
		game->player.ply_x = new_x;
	}

	// Check collision for Y movement
	map_x = (int)(game->player.ply_x / game->img.cell_size);
	map_y = (int)(new_y / game->img.cell_size);
	if (map_x >= 0 && map_x < 25 &&
		map_y >= 0 && map_y < 17 &&
		game->map[map_y][map_x] != '1')
	{
		game->player.ply_y = new_y;
	}
}

void draw_player(t_game *game)
{
	int size;
	int y;
	int x;
	int pixel_x;
	int pixel_y;
	int i;

	i = 0;
	size = 5;
	pixel_x = (int)game->player.ply_x;
	pixel_y = (int)game->player.ply_y;

	// Draw player circle
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			if (x * x + y * y <= size * size)
				my_mlx_pixel_put(&game->img, pixel_x + x, pixel_y + y, 0xFF0000);
			x++;
		}
		y++;
	}

	// Draw direction line using DDA algorithm
	int line_end_x = pixel_x + (int)(game->player.player_dir_x * 20);
	int line_end_y = pixel_y + (int)(game->player.player_dir_y * 20);

	// Simple DDA line drawing
	int dx = line_end_x - pixel_x;
	int dy = line_end_y - pixel_y;
	int steps;

	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	if (steps > 0)
	{
		float x_inc = dx / (float)steps;
		float y_inc = dy / (float)steps;
		float current_x = pixel_x;
		float current_y = pixel_y;

		while (i <= steps)
		{
			my_mlx_pixel_put(&game->img, (int)current_x, (int)current_y, 0x00FF00);
			current_x += x_inc;
			current_y += y_inc;
			i++;
		}
	}
}

int handle_key(int keycode, t_game *game)
{
	double move = game->player.move_speed * game->img.cell_size;

	if (keycode == 65307) // ESC
		exit(0);

	// Forward
	if (keycode == 'w')
		move_player(game, game->player.player_dir_x * move, game->player.player_dir_y * move);
	// Backward
	else if (keycode == 's')
		move_player(game, -game->player.player_dir_x * move, -game->player.player_dir_y * move);
	// Strafe left
	else if (keycode == 'a')
		move_player(game, -game->player.plane_x * move, -game->player.plane_y * move);
	// Strafe right
	else if (keycode == 'd')
		move_player(game, game->player.plane_x * move, game->player.plane_y * move);
	// Rotate left
	else if (keycode == 65361) // Left arrow
		rotate_player(game, -game->player.rot_speed);
	// Rotate right
	else if (keycode == 65363) // Right arrow
		rotate_player(game, game->player.rot_speed);

	// DON'T call render(game) here - let render_3d handle it automatically
	return (0);
}

void init_player(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'W' || game->map[y][x] == 'E' || 
				game->map[y][x] == 'N' || game->map[y][x] == 'S')
			{
				// Set player position to center of cell in PIXELS
				game->player.ply_x = (x * game->img.cell_size) + (game->img.cell_size / 2);
				game->player.ply_y = (y * game->img.cell_size) + (game->img.cell_size / 2);
				game->player.move_speed = 0.1;
				game->player.rot_speed = 0.05;
				game->player.player_dir = game->map[y][x];

				if (game->player.player_dir == 'N')
				{
					game->player.player_dir_x = 0.0;
					game->player.player_dir_y = -1.0;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0.0;
				}
				else if (game->player.player_dir == 'S')
				{
					game->player.player_dir_x = 0.0;
					game->player.player_dir_y = 1.0;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0.0;
				}
				else if (game->player.player_dir == 'E')
				{
					game->player.player_dir_x = 1.0;
					game->player.player_dir_y = 0.0;
					game->player.plane_x = 0.0;
					game->player.plane_y = 0.66;
				}
				else if (game->player.player_dir == 'W')
				{
					game->player.player_dir_x = -1.0;
					game->player.player_dir_y = 0.0;
					game->player.plane_x = 0.0;
					game->player.plane_y = -0.66;
				}
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Error: Player not found in map!\n");
}
