#include "../includes/cub3d.h"

int render(t_game *game)
{
    int y;
    int x;
    char tile;
    int color;

    game->y_map = 0;
    while (game->map[game->y_map])
    {
        game->x_map = 0;
        while (game->map[game->y_map][game->x_map])
        {
            tile = game->map[game->y_map][game->x_map];
            if (tile == '1')
                color = 0x725349;
            else if (tile == '0')
                color = 0x7a8f33;
            y = 0;
            while (y < game->img.cell_size)
            {
                x = 0;
                while (x < game->img.cell_size)
                {
                    my_mlx_pixel_put(&game->img, game->x_map * game->img.cell_size + x, game->y_map * game->img.cell_size + y, color);
                    x++;
                }
                y++;
            }
            game->x_map++;
        }
        game->y_map++;
    }
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
    return (0);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= 800 || y >= 600)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int init_win(t_game *game)
{
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return 0;
    game->win_ptr = mlx_new_window(game->mlx_ptr, game->width, game->height, "cub3d");
    if (!game->win_ptr)
        return (0);

    game->img.img_ptr = mlx_new_image(game->mlx_ptr, game->width, game->height);
    game->img.addr = mlx_get_data_addr(game->img.img_ptr,
                &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);

    mlx_loop_hook(game->mlx_ptr, render_3d, game); // render loop - ONLY 3D!
    mlx_hook(game->win_ptr, 2, 1l<<0, handle_key, game);
    mlx_loop(game->mlx_ptr);
    return (1);
}

