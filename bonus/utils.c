/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasserao <hasserao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:00:49 by hasserao          #+#    #+#             */
/*   Updated: 2023/01/27 05:33:34 by hasserao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	len_s;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		if (start == 0)
			len_s = ft_strlen(s);
		else
			len_s = ft_strlen(s + start);
	}
	if (len >= len_s)
		len = len_s;
	p = (char *)malloc((len + 1) * sizeof (char));
	if (!p)
		return (NULL);
	else
		ft_strlcpy(p, s + start, len + 1);
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*(unsigned char *)s1 || *(unsigned char *)s2) && i < n)
	{
		if (*(unsigned char *)s1 > *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		else
			if (*(unsigned char *)s1 < *(unsigned char *)s2)
				return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
