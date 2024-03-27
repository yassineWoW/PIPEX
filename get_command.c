/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:29:57 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/27 23:19:11 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpaths(char *envp[])
{
	char	*string;
	int		i;
	char	*env_paths;

	i = 0;
	while (envp[i])
	{
		string = ft_strstr(envp[i], "PATH=");
		i++;
		if (string != NULL)
			break ;
	}
	if (string == NULL)
		write(2, "enviroment PATH not found :\n", 27);
	env_paths = string + 5;
	return (env_paths);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if ((s[i] == '\0'))
		{
			return (0);
		}
		i++;
	}
	return ((char *)&s[i]);
}

void	free_split(char **command_av)
{
	int	i;

	i = 0;
	while (command_av[i])
	{
		free(command_av[i]);
		i++;
	}
	free(command_av);
}

char	*get_command(char **command_av, char *envp[])
{
	char	*bin_paths;
	char	**paths;
	char	*s;
	char	*command_path;
	int		i;

	i = 0;
	if (command_av[0] == NULL)
		return (NULL);
	if (ft_strchr(command_av[0], '/'))
		return (command_av[0]);
	bin_paths = getpaths(envp);
	paths = ft_split(bin_paths, ':');
	command_path = ft_strjoin("/", command_av[0]);
	while (paths[i] != NULL)
	{
		s = ft_strjoin(paths[i], command_path);
		if (!access(s, F_OK))
			return (free(command_path), s);
		else
			(free(s), free(paths[i]));
		i++;
	}
	(free_split(command_av), free(paths), free(command_path));
	return (NULL);
}
