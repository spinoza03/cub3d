#include "../../include/cub.h"

static unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	render_3d(t_game *game)
{
	int		x;
	int		y;
	double	perpWallDist;
	double	posX;
	double	posY;
	t_img	*texture; // Ptr to the texture we'll use for this wall
	double	wallX; // The exact x-coord where the ray hit the wall (0.0 to 1.0)
	int		texX; // The x-coord on the texture (0 to 63)
	int		texY; // The y-coord on the texture (0 to 63)
	double	step; // How much to increase texY for each screen pixel
	double	texPos; // The starting vertical texture position
	unsigned int	color;

	// (This part is from your friend's original code, it's just split up)
	// --- Start of raycasting DDA loop ---
	posX = game->player.ply_x / game->img.cell_size;
	posY = game->player.ply_y / game->img.cell_size;
	x = 0;
	while (x < game->width)
	{
		double	sideDistX;
		double	sideDistY;
		int		lineHeight;
		int		drawStart;
		int		drawEnd;

		game->camera.cameraX = 2 * x / (double)game->width - 1;
		game->camera.raydirx = game->player.player_dir_x + game->player.plane_x * game->camera.cameraX;
		game->camera.raydiry = game->player.player_dir_y + game->player.plane_y * game->camera.cameraX;
		game->camera.mapX = (int)posX;
		game->camera.mapY = (int)posY;
		if (game->camera.raydirx == 0)
			game->camera.deltaDistX = 1e30;
		else
			game->camera.deltaDistX = fabs(1 / game->camera.raydirx);
		if (game->camera.raydiry == 0)
			game->camera.deltaDistY = 1e30;
		else
			game->camera.deltaDistY = fabs(1 / game->camera.raydiry);
		if (game->camera.raydirx < 0)
		{
			game->camera.stepX = -1;
			sideDistX = (posX - game->camera.mapX) * game->camera.deltaDistX;
		}
		else
		{
			game->camera.stepX = 1;
			sideDistX = (game->camera.mapX + 1.0 - posX) * game->camera.deltaDistX;
		}
		if (game->camera.raydiry < 0)
		{
			game->camera.stepY = -1;
			sideDistY = (posY - game->camera.mapY) * game->camera.deltaDistY;
		}
		else
		{
			game->camera.stepY = 1;
			sideDistY = (game->camera.mapY + 1.0 - posY) * game->camera.deltaDistY;
		}
		game->camera.hit = 0;
		while (game->camera.hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += game->camera.deltaDistX;
				game->camera.mapX += game->camera.stepX;
				game->camera.side = 0;
			}
			else
			{
				sideDistY += game->camera.deltaDistY;
				game->camera.mapY += game->camera.stepY;
				game->camera.side = 1;
			}
			if (game->camera.mapY >= 0 && game->camera.mapX >= 0 &&
				game->camera.mapY < game->map_height && game->camera.mapX < game->map_width)
			{
				if (game->map[game->camera.mapY][game->camera.mapX] == '1')
					game->camera.hit = 1;
			}
			else
				game->camera.hit = 1;
		}
		if (game->camera.side == 0)
			perpWallDist = (sideDistX - game->camera.deltaDistX);
		else
			perpWallDist = (sideDistY - game->camera.deltaDistY);
		if (perpWallDist < 0.0001)
			perpWallDist = 0.0001;
		lineHeight = (int)(game->height / perpWallDist);
		drawStart = -lineHeight / 2 + game->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + game->height / 2;
		if (drawEnd >= game->height)
			drawEnd = game->height - 1;
		
		// --- END of DDA loop ---
		// --- START of NEW Texture Calculation ---

		// 1. Choose the correct texture based on which wall we hit
		if (game->camera.side == 1) // N/S Wall
		{
			if (game->camera.raydiry > 0)
				texture = &game->tex_south;
			else
				texture = &game->tex_north;
		}
		else // E/W Wall
		{
			if (game->camera.raydirx > 0)
				texture = &game->tex_east;
			else
				texture = &game->tex_west;
		}

		// 2. Calculate 'wallX' (where the ray hit on the wall, from 0.0 to 1.0)
		if (game->camera.side == 0)
			wallX = posY + perpWallDist * game->camera.raydiry;
		else
			wallX = posX + perpWallDist * game->camera.raydirx;
		wallX -= floor(wallX); // Get just the fractional part

		// 3. Calculate 'texX' (the x-coordinate on the texture, 0 to 63)
		texX = (int)(wallX * (double)TEX_WIDTH);
		// Flip the texture if it's mirrored
		if (game->camera.side == 0 && game->camera.raydirx > 0)
			texX = TEX_WIDTH - texX - 1;
		if (game->camera.side == 1 && game->camera.raydiry < 0)
			texX = TEX_WIDTH - texX - 1;

		// 4. Calculate 'step' and 'texPos' (for vertical texture mapping)
		step = 1.0 * TEX_HEIGHT / lineHeight;
		texPos = (drawStart - game->height / 2 + lineHeight / 2) * step;

		// --- END of NEW Texture Calculation ---

		// Draw Ceiling (Unchanged)
		y = 0;
		while (y < drawStart)
		{
			my_mlx_pixel_put(&game->img, x, y, game->ceiling_color);
			y++;
		}
		
		// Draw Wall (This loop is now new)
		y = drawStart;
		while (y < drawEnd)
		{
			// Get the y-coordinate on the texture
			texY = (int)texPos & (TEX_HEIGHT - 1);
			texPos += step; // Move to the next texture pixel for the next screen pixel
			
			// Get the color from the texture
			color = get_texture_pixel(texture, texX, texY);
			
			// (Optional) Darken N/S walls to give a pseudo-3D effect
			if (game->camera.side == 1)
				color = (color >> 1) & 8355711; // Halves the brightness
			
			my_mlx_pixel_put(&game->img, x, y, color);
			y++;
		}
		
		// Draw Floor (Unchanged)
		y = drawEnd;
		while (y < game->height)
		{
			my_mlx_pixel_put(&game->img, x, y, game->floor_color);
			y++;
		}
		
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
	return (0);
}