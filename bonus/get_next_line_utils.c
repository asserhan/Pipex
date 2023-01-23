/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:49:26 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/23 00:58:31 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l_dst;
	size_t	l_src;

	l_src = ft_strlen(src);
	i = 0;
	if (dstsize == 0 && !dst)
		return (l_src);
	l_dst = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= l_dst)
		return (l_src + dstsize);
	while (src[i] && (i + l_dst) < dstsize - 1)
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	len ;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(len + 1 * sizeof(char));
	if (!p)
		return (NULL);
	else
	{
		ft_strlcpy(p, s1, ft_strlen(s1) + 1);
		ft_strlcat(p, s2, len + 1);
	}
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(char *)s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*(char *)s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}
