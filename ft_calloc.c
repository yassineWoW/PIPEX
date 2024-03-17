/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:42:34 by yimizare          #+#    #+#             */
/*   Updated: 2024/02/18 16:56:07 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*string;

	i = 0;
	string = s;
	while (i < n)
	{
		string[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloccee;

	if (size < 0)
		return (NULL);
	if (size && count > SIZE_MAX / size)
		return (NULL);
	alloccee = (void *)malloc(count * size);
	if (alloccee == NULL)
		return (NULL);
	ft_bzero(alloccee, (count * size));
	return (alloccee);
}
