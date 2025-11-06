#include "../../include/cub.h"

void rotate_player(t_game *game, double angle)
{
	double old_dir_x;
	double old_plane_x;
	
	old_dir_x = game->player.player_dir_x;
	old_plane_x = game->player.plane_x;
	
	game->player.player_dir_x = game->player.player_dir_x * cos(angle) - game->player.player_dir_y * sin(angle);
	game->player.player_dir_y = old_dir_x * sin(angle) + game->player.player_dir_y * cos(angle);
	
	game->player.plane_x = game->player.plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}
