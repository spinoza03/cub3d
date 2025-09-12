/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:19:08 by ilallali          #+#    #+#             */
/*   Updated: 2025/09/11 13:37:36 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*des;
	unsigned char		*str;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	des = (unsigned char *)dst;
	str = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		des[i] = str[i];
		i++;
	}
	return (dst);
}

static int	check(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*trimedone(const char *s1, size_t start, size_t end)
{
	char	*trim;
	size_t	i;

	trim = (char *)malloc(end - start + 2);
	if (!trim)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (*s1 == '\0')
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && check(s1[start], set))
		start++;
	while (end > start && check(s1[end], set))
		end--;
	return (trimedone(s1, start, end));
}
