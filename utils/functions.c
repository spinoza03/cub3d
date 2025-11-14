/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:07:36 by allali            #+#    #+#             */
/*   Updated: 2025/11/14 14:53:03 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (c == '\0')
		return ((char *)&str[i]);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_pustr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> content = content;
	new -> next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	if (!lst || !new_node)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new_node;
	else
		*lst = new_node;
}
