/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 15:11:38 by ilallali          #+#    #+#             */
/*   Updated: 2025/11/14 15:26:15 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*ft_strchr1(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((unsigned char)str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (NULL);
}

void	populate_arr(t_list *head, t_game *game)
{
	int				i;
	t_list			*current;
	unsigned int	longest;

	i = 0;
	longest = 0;
	current = head;
	game->map_height = ft_lstsize(head);
	while (current != NULL)
	{
		if (longest < ft_strlen(current->content))
			longest = ft_strlen(current->content);
		current = current->next;
	}
	game->map_width = longest;
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	i = 0;
	while (head != NULL)
	{
		game->map[i] = ft_strdup(head->content);
		head = head->next;
		i++;
	}
	game->map[game->map_height] = NULL;
}
