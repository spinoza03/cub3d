#include "../includes/cub3d.h"

int    render_3d(t_game *game)
{
    int x;
    double  sideDistX;
    double  sideDistY;
    double perpWallDist;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int y;
    int color;
    double posX;
    double posY;
    
    // Convert player position from pixels to map coordinates
    posX = game->player.ply_x / game->img.cell_size;
    posY = game->player.ply_y / game->img.cell_size;
    
    x = 0;
    while (x < game->width)
    {
        // Step 1: Calculate ray direction
        game->camera.cameraX = 2 * x / (double)game->width - 1;
        game->camera.raydirx = game->player.player_dir_x + game->player.plane_x * game->camera.cameraX;
        game->camera.raydiry = game->player.player_dir_y + game->player.plane_y * game->camera.cameraX;

        // Step 2: Map position
        game->camera.mapX = (int)posX;
        game->camera.mapY = (int)posY;
        
        // Step 3: Length of ray from one side to next in X or Y
        if (game->camera.raydirx == 0)
            game->camera.deltaDistX = 1e30;
        else
            game->camera.deltaDistX = fabs(1 / game->camera.raydirx);
            
        if (game->camera.raydiry == 0)
            game->camera.deltaDistY = 1e30;
        else
            game->camera.deltaDistY = fabs(1 / game->camera.raydiry);
        
        // Step 4: Calculate step and initial sideDist
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
        
        // Step 5: DDA (Digital Differential Analysis)
        game->camera.hit = 0;
        while (game->camera.hit == 0)
        {
            // Jump to next square in X or Y
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
            
            // Check if ray has hit a wall
            if (game->camera.mapY >= 0 && game->camera.mapX >= 0 &&
                game->camera.mapY < 17 && game->camera.mapX < 25)
            {
                if (game->map[game->camera.mapY][game->camera.mapX] == '1')
                    game->camera.hit = 1;
            }
            else
            {
                // Hit map boundary, treat as wall
                game->camera.hit = 1;
            }
        }
        
        // Step 6: Calculate distance to wall
        if (game->camera.side == 0)
            perpWallDist = (sideDistX - game->camera.deltaDistX);
        else
            perpWallDist = (sideDistY - game->camera.deltaDistY);
        
        // Prevent division by zero
        if (perpWallDist < 0.0001)
            perpWallDist = 0.0001;
        
        // Step 7: Calculate wall height on screen
        lineHeight = (int)(game->height / perpWallDist);
        drawStart = -lineHeight / 2 + game->height / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + game->height / 2;
        if (drawEnd >= game->height)
            drawEnd = game->height - 1;
        
        // Step 8: Choose wall color based on side
        if (game->camera.side == 1)
            color = 0x808080; // Darker for horizontal walls
        else
            color = 0xFFFFFF; // Brighter for vertical walls
        
        // Draw ceiling
        y = 0;
        while (y < drawStart)
        {
            my_mlx_pixel_put(&game->img, x, y, 0x333333); // Dark gray ceiling
            y++;
        }
        
        // Draw wall
        y = drawStart;
        while (y < drawEnd)
        {
            my_mlx_pixel_put(&game->img, x, y, color);
            y++;
        }
        
        // Draw floor
        y = drawEnd;
        while (y < game->height)
        {
            my_mlx_pixel_put(&game->img, x, y, 0x555555); // Gray floor
            y++;
        }
        
        x++;
    }
    
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
    return 0;
}
