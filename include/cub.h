/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bael-bad <bael-bad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:01:58 by bael-bad          #+#    #+#             */
/*   Updated: 2025/11/16 18:31:02 by bael-bad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
#include <mlx.h>

# define BUFFER_SIZE 1024
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define COUNT 125

// KEYCODE FOR MACOS
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		cell_size;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_draw_data
{
	int		x;
	int		*draw;
	t_img	*texture;
	int		tex_x;
}	t_draw_data;

typedef struct s_camera
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	double	delta_dist_x;
	double	delta_dist_y;
}	t_camera;

typedef struct s_plr
{
	double	ply_x;
	double	ply_y;
	double	move_speed;
	char	player_dir;
	double	player_dir_y;
	double	player_dir_x;
	double	plane_x;
	double	plane_y;
	double	rot_speed;
}	t_plr;

typedef struct s_flag
{
	int	no;
	int	east;
	int	so;
	int	we;
	int	floor;
	int	cealing;
}	t_flag;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_plr		player;
	t_camera	camera;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_east;
	t_img		tex_west;
	int			width;
	int			height;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			player_x;
	int			player_y;
	char		player_dir_char;
	int			map_height;
	int			map_width;
	t_flag		flags;
    int         key[COUNT];
}	t_game;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void			populate_arr(t_list *head, t_game *game);
void			init_data(t_game *game);
int				check_sum(t_game *game, t_list **head);
int				check_count(char **colors, int *final_color);
int				is_valid_integer(char *str);
void			ft_free_split(char **arr);
void			free_all_data(t_game *game);
void			ft_lstclear(t_list **lst, void (*del)(void *));
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s);
char			*ft_strtrim(const char *s1, const char *set);
int				start_parsing(t_game *game, char *file);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strrchr(const char *str, int c);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t n);
void			ft_pustr_fd(char *str, int fd);
int				ft_strchr(const char *str, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*get_next_line(int fd);
char			*ft_substr(char const *s, size_t start, size_t len);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new_node);
t_list			*ft_lstlast(t_list *lst);
char			*ft_strchr1(const char *str, int c);
int				ft_isdigit(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			**ft_split(const char *s, char c);
int				ft_lstsize(t_list *lst);
int				init_game(t_game *game);
int				render(t_game *game);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				init_win(t_game *game);
void			init_var(t_game *game);
void			init_player(t_game *game);
int				handle_key(t_game *game);
void			draw_player(t_game *game);
void			rotate_player(t_game *game, double angle);
void			move_player(t_game *game, double dx, double dy);
int				render_3d(t_game *game);
int				ft_abs(int n);
int				load_textures(t_game *game);
int				pars_map(char *line, t_list **head);
int				pars_texture(char *line, char **texture_ptr, int *flag);
int				pars_color(char *line, int *color_ptr, int *flag);
int				pars_conf(char *line, t_game *game, t_list **head);
int				pars_map_validation(t_game *game);
void			calc_step_and_dda(t_game *game, double *pos, double *side_d);
void			calc_wall_params(t_game *game, double *side_d, int *draw);
void			render_column(t_game *game, int x, double *pos, int *draw);
unsigned int	get_texture_pixel(t_img *tex, int x, int y);
int    key_press(int keycode, t_game *game);
int    key_release(int keycode, t_game *game);

#endif
