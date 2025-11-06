#include "includes/cub3d.h"

void    init_var(t_game *game)
{
    game->x_map = 0;
    game->y_map = 0;
    game->player.ply_x = 0;
    game->player.ply_y = 0;
    game->player.move_speed = 0.1;
}