/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:10:56 by allali            #+#    #+#             */
/*   Updated: 2025/09/18 16:28:25 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
#include <limits.h>
// # include <mlx.h>
#include "../minilibx-linux/mlx.h"
#  define BUFFER_SIZE 1024

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_flag
{
	int no;
	int east;
	int so;
	int we;
	int	floor;
	int cealing;
} t_flag;

typedef struct s_data
{
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    int     floor_color;
    int     ceiling_color;
    char    **map;
	int		player_x;
	int		player_y;
	char	player_dir;
    int     map_height;
    int     map_width;
	t_flag	flags;
}   t_data;

typedef struct s_game
{
    void    *mlx_ptr;
    void    *win_ptr;
    t_data  data;
    t_img   frame;
}   t_game;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void    free_game_data(t_data *data);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *s1, const char *set);
int		start_parsing(t_game *game, char *file);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(const char *str, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
void	ft_pustr_fd(char *str, int fd);
int		ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*get_next_line(int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new_node);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strchr1(const char *str, int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(const char *s, char c);
int		ft_lstsize(t_list *lst);
int	init_game(t_game *game);
int	render(t_game *game);
#endif
