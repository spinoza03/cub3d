#include "includes/cub3d.h"

char **get_map(t_game *game)
{
    char **map = malloc(sizeof(char *) * 18);
    if (!map)
        return NULL;

    map[0]  = "1111111111111111111111111";
    map[1]  = "1000000000110000000000001";
    map[2]  = "1011000001110000000000001";
    map[3]  = "1001000000000000N00000001";
    map[4]  = "1111111110110000011100001";
    map[5]  = "1000000000110000011101111";
    map[6]  = "1111011111111101110001001";
    map[7]  = "1111011111111101110101001";
    map[8]  = "1100000011010101110000001";
    map[9]  = "1000000000000000110000001";
    map[10] = "1000000000000000110101001";
    map[11] = "1111011111111101110000001";
    map[12] = "1111011111111101110101001";
    map[13] = "1000000000110000011100001";
    map[14] = "1000000000110000011100001";
    map[15] = "1000000000000000000000001";
    map[16] = "1111111111111111111111111";
    map[17] = NULL;

    // Count rows
    int i = 0;
    while (map[i] != NULL)
        i++;

    // Set map dimensions in GRID COORDINATES
    game->y_map = i;  // 17 rows
    game->x_map = strlen(map[0]);  // 25 columns

    // Set window size
    game->img.cell_size = 32;
    game->width = 800;   // Window width
    game->height = 600;  // Window height

    printf("Map grid size: %d x %d\n", game->y_map, game->x_map);
    printf("Window size: %d x %d\n", game->width, game->height);

    return map;
}

int main(void)
{
    t_game game;
    int i;

    game.map = get_map(&game);

    printf("Map dimensions: %d rows x %d cols\n", game.y_map, game.x_map);

    // Print map
    i = 0;
    while (game.map[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }
    
    init_player(&game);
    
    printf("Player position: %.2f, %.2f (pixels)\n", game.player.ply_x, game.player.ply_y);
    printf("Player position: %.2f, %.2f (map coords)\n", 
           game.player.ply_x / game.img.cell_size, 
           game.player.ply_y / game.img.cell_size);
    
    if (!init_win(&game))
        return (1);
        
    free(game.map);
    return 0;
}



