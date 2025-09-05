/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:10:56 by allali            #+#    #+#             */
/*   Updated: 2025/09/04 21:55:45 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
// # include <mlx.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21474836475
# endif
typedef struct s_map
{
	char	*grid;
	s_map	*next;
}	t_map;

typedef struct s_game
{
	t_map	*map;
} t_game;
/* FUNCTIONS */
int	ft_strcmp(char *s1, char *s2);
char	*ft_strrchr(const char *str, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);

int		ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, size_t start, size_t len);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);

#endif