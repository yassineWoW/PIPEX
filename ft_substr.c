/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:49:25 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/18 17:25:31 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;

	i = 0;
	if (destsize != 0)
	{
		while (src[i] != '\0' && i < destsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	end;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	end = 0;
	if (len == 0 || start >= slen)
		return (ft_calloc(1, 1));
	if (start < slen)
		end = slen - start;
	if (end > len)
		end = len;
	new = (char *)ft_calloc(end + 1, 1);
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, end + 1);
	return (new);
}
