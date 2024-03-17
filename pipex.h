/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:21:54 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/17 14:57:33 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>


int		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strjoin(char const *s1, char const *s2);
char	*getpaths(char *envp[]);
char	*get_command(char **command_av, char *envp[]);
void	pipex(char *argv[], char *envp[]);
void	waiting();

#endif