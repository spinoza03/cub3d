/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:50:22 by allali            #+#    #+#             */
/*   Updated: 2025/09/20 17:34:59 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"
#include <stdlib.h>

void    ft_free_split(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int	is_valid_integer(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
int	check_count(char **colors, int *final_color)
{
	int	i;
	int	c[3];

	i = 0;
	if (!colors[i] || colors[i][0] == '\0')
		return (0);
	while (colors[i])
	{
		if (!is_valid_integer(colors[i]))
			return (0);
		c[i] = ft_atoi(colors[i]);
		if(c[i] > 255 || c[i] < 0)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	*final_color = (c[0] << 16 | c[1] << 8 | c[2]);
	return (1);
}
int pars_map(char *line, t_list **head)
{
    char    *duped;
    t_list  *new_node;
	int		len;

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    duped = ft_strdup(line);
    if (!duped)
        return (0);
    new_node = ft_lstnew(duped);
    if (!new_node)
    {
        free(duped);
        return (0);
    }
    ft_lstadd_back(head, new_node);
    return (1);
}
int pars_texture(char *line, char **texture_ptr, int *flag)
{
	int		fd;
	char	*trimed;

	fd = 0;
	if(*flag == 1)
		return (0);
	trimed = ft_strtrim(line, " \n");
	fd = open(trimed, O_RDONLY);
	if (fd == -1)
	{
		free(trimed);
		return 0;
	}
	else
		*texture_ptr = ft_strdup(trimed);
	*flag = 1;
	close(fd);
	free(trimed);
	return (1);
}

int pars_color(char *line, int *color_ptr, int *flag)
{
	char	**splited;
	int		i;

	i = 0;
	while (line[i])
	{
		if(line[i] == ',' && line[i + 1]  == ',')
			return (0);
		i++;
	}
	splited = ft_split(line, ',');
	if(*flag == 1 || !check_count(splited, color_ptr))
	{
		ft_free_split(splited);
		return 0;
	}
	ft_free_split(splited); 
	*flag = 1;
	return 1;
}
int	pars_conf(char *line, t_data *data, t_list **head)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return(pars_texture(line + 3, &data->north_texture, &data->flags.no));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return(pars_texture(line + 3, &data->south_texture, &data->flags.so));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return(pars_texture(line + 3, &data->east_texture, &data->flags.east));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return(pars_texture(line + 3, &data->west_texture, &data->flags.we));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (pars_color(line + 2, &data->floor_color, &data->flags.floor));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (pars_color(line + 2, &data->ceiling_color, &data->flags.cealing));
	else if (ft_strncmp(line, "0", 1) == 0 || ft_strncmp(line, "1", 1) == 0)
		return (pars_map(line, head));
	else
	{
		if(line[0] == '\n')
			return (1);
		return (0);
	}
}

int read_file(t_game *game, char *file, t_list **head)
{
	char	*line;
	int		fd;
	char	*ptr;

	fd = open(file , O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if(!line)
			break;
		ptr = line;
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (*line == '\n' || *line == '\0')
		{
			free(line);
			continue;
		}
		if (!pars_conf(ptr, &game->data, head))
    		return (free(line), 0);
		free(line);
	}
	return (1);
}
void	populate_arr(t_list *head, t_game *game)
{
	int		i;

	i = 0;
	while (head != NULL)
	{
		game->data.map[i] = ft_strdup(head->content);
		head = head->next;
		i++;
	}
	game->data.map[game->data.map_height] = NULL;
}
void    debug_print_data(t_data *data)
{
    int i;

    printf("\n--- 📝 PARSED DATA ---\n");
    printf("North Texture:  [%s]\n", data->north_texture);
    printf("South Texture:  [%s]\n", data->south_texture);
    printf("East Texture:   [%s]\n", data->east_texture);
    printf("West Texture:   [%s]\n", data->west_texture);
    printf("Floor Color:    %#08x\n", data->floor_color);
    printf("Ceiling Color:  %#08x\n", data->ceiling_color);
    printf("Map Height:     %d\n", data->map_height);
    printf("Map Width:      %d\n", data->map_width);
    printf("--- 🗺️ MAP GRID ---\n");
    if (!data->map)
    {
        printf("Map not loaded.\n");
        return ;
    }
    i = 0;
    while (data->map[i])
    {
        printf("%s\n", data->map[i]);
        i++;
    }
    printf("-----------------------\n\n");
}
int	check_sum(t_game *game, t_list **head)
{
	int flag_sum;
	flag_sum = game->data.flags.no + game->data.flags.so + 
               game->data.flags.we + game->data.flags.east + 
               game->data.flags.floor + game->data.flags.cealing;
    if (flag_sum != 6)
    {
        ft_pustr_fd("Error: Missing one or more configurations.\n", 2);
        ft_lstclear(head, free);
        return (0);
    }
	return (1);
}
void    free_game_data(t_data *data)
{
    // Free the four texture paths
    free(data->north_texture);
    free(data->south_texture);
    free(data->east_texture);
    free(data->west_texture);
    if (data->map)
        ft_free_split(data->map);
}

int	start_parsing(t_game *game, char *file)
{
	t_list				*head;
	unsigned int		longest;
	t_list				*current;

	head = NULL;
	longest = 0;
	if (!read_file(game, file, &head))
		return (0);
	if(!check_sum(game, &head))
		return (0);
	current = head;
	game->data.map_height = ft_lstsize(head);
	while(current != NULL)
	{
		if(longest < ft_strlen(current->content))
			longest = ft_strlen(current-> content);
		current = current->next;
	}
	game->data.map_width = longest;
	game->data.map = malloc(sizeof(char *) * (game->data.map_height + 1));
	populate_arr(head, game);
	ft_lstclear(&head, free);
	// debug_print_data(&game->data);
	return 1;
}
