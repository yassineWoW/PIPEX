/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:24:11 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/27 23:14:55 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *command_argv, char **envp, char *command_path)
{
	char	**cmd;
	char	*error_msg;
	int		i;

	i = 0;
	cmd = ft_split(command_argv, ' ');
	if (execve(command_path, cmd, envp) == -1)
	{
		error_msg = ft_strjoin("zsh: command not found: ", cmd[0]);
		write(2, error_msg, ft_strlen(error_msg));
		write(2, "\n", 1);
		if (cmd)
		{
			while (cmd[i])
				free(cmd[i++]);
			free(cmd);
			free(error_msg);
			free(command_path);
			exit(127);
		}
	}
}

static void	child1(char *argv[], int *fdp, char *envp[], char *command)
{
	int	fd;

	if (access(argv[1], F_OK) == -1)
	{
		perror(argv[1]);
		exit(127);
	}
	if (ft_strlen(argv[2]) == 0)
	{
		write(2, "zsh permission denied: \n", 24);
		exit(127);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 || dup2(fd, 0) == -1 || dup2(fdp[1], 1) == -1)
	{
		perror("in-file failed");
	}
	close(fdp[0]);
	ft_execute(argv[2], envp, command);
}

static void	child2(char *argv[], int *fdp, char *envp[], char *command)
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1 || dup2(fd, 1) == -1 || dup2(fdp[0], 0) == -1)
	{
		perror("out-file failed");
		exit(0);
	}
	if (ft_strlen(argv[3]) == 0)
	{
		write(2, "zsh permission denied:\n", 23);
		exit(127);
	}
	close(fdp[1]);
	ft_execute(argv[3], envp, command);
}

void	pipex(char *argv[], char *envp[])
{
	char	**s;

	int (pid1), (pid2), (fdp[2]);
	if (pipe(fdp) < 0)
		perror("pipe error");
	pid1 = fork();
	if (pid1 < 0)
		perror("forking gone wrong");
	if (pid1 == 0)
	{
		s = ft_split(argv[2], ' ');
		child1(argv, fdp, envp, get_command(s, envp));
	}
	else
	{
		wait(NULL);
		pid2 = fork();
		if (pid2 < 0)
			perror("forking gone wrong");
		if (pid2 == 0)
			child2(argv, fdp, envp, get_command(ft_split(argv[3], ' '), envp));
	}
	(close(fdp[0]), close(fdp[1]));
}
