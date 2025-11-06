#include "../../include/cub.h"

void clear_screen(t_game *game, int color)
{
    int x;
    int y;

    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            my_mlx_pixel_put(&game->img, x, y, color);
            x++;
        }
        y++;
    }
}