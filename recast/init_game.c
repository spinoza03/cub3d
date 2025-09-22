#include "../include/cub.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

int	render(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->data.map_width && i < game->data.map_height)
	{
		put_pixel(&game->frame, i, i, 0xFFFFFF);
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->frame.img, 0, 0);
	return (0);
}
int init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return 0;
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->data.map_width, game->data.map_height, "mok.cub");
	if (!game->win_ptr)
		return (0);
	game->frame.img = mlx_new_image(game->mlx_ptr,  game->data.map_width,game->data.map_height);
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	// printf("<<<%s>>>\n", game->frame.addr);

	return 1;
}
