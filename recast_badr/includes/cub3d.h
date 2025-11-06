#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
#include <mlx.h>
#include <string.h>
# include "../minilibx-linux/mlx.h"
#include <math.h>

typedef struct s_camera
{
    double cameraX;
    double raydirx;
    double raydiry;
    int     mapX;
    int     mapY;
    int     stepX;
    int     stepY;
    int     hit;
    int     side;
    int     line;
    double deltaDistX;
    double deltaDistY;
}   t_camera;
typedef struct s_plr{
    double ply_x;
    double ply_y;
    double move_speed;
    char player_dir;
    double player_dir_x;  // Changed from int to double
    double player_dir_y;  // Changed from int to double
    double plane_x;
    double plane_y;
    double rot_speed;
}   t_plr;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     cell_size;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_game {
    void *mlx_ptr;
    void *win_ptr;
    char **map;
    int width;
    int x_map;
    int y_map;
    int height;
    t_plr player;
    t_camera camera;
    t_img img;
} t_game;

// Function declarations
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int  render(t_game *game);
int  init_win(t_game *game);
void    init_var(t_game *game);
void    init_player(t_game *game);
int handle_key(int keycode, t_game *game);
void    draw_player(t_game *game);
void clear_screen(t_game *game, int color);
void rotate_player(t_game *game, double angle);
void move_player(t_game *game, double dx, double dy);
int    render_3d(t_game *game);
int	ft_abs(int n);

#endif