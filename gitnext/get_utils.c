/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:58:39 by ilallali          #+#    #+#             */
/*   Updated: 2025/09/12 15:17:48 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(s)+ 1);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	l;
	size_t	i;

	l = 0;
	while (src[l])
	{
		l++;
	}
	if (n > 0)
	{
		i = 0;
		while (i < n - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (l);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	srcl;
	size_t	destl;
	size_t	in;

	srcl = ft_strlen(src);
	destl = 0;
	in = 0;
	if (!dst && n == 0 && src)
		return (srcl);
	while (dst[destl] && destl < n)
		destl++;
	if (destl == n)
		return (n + srcl);
	while (src[in] && (destl + in) < (n - 1))
	{
		dst[destl + in] = src[in];
		in++;
	}
	dst[destl + in] = '\0';
	return (destl + srcl);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	l1;
	size_t	l2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (!str)
		return (free(s1), s1 = NULL, NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	free(s1);
	return (str);
}
