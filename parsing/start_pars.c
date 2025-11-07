/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:50:22 by allali            #+#    #+#             */
/*   Updated: 2025/11/07 16:53:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	is_line_whitespace(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	read_file(t_game *game, char *file, t_list **head)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_pustr_fd("Error: Cannot open file.\n", 2);
		return (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (is_line_whitespace(line))
		{
			if (*head != NULL)
			{
				ft_pustr_fd("Error: Empty line within map definition.\n", 2);
				free(line);
				close(fd);
				return (0);
			}
			free(line);
			continue;
		}
		if (!pars_conf(line, game, head))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}
void	populate_arr(t_list *head, t_game *game)
{
	int		i;
	t_list	*current;
	unsigned int		longest;

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

int	start_parsing(t_game *game, char *file)
{
	t_list				*head;

	head = NULL;
	if (!read_file(game, file, &head))
		return (0);
	if (!check_sum(game, &head))
		return (0);
	populate_arr(head, game);
	ft_lstclear(&head, free);
	return (1);
}
