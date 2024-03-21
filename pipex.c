/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:24:11 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/21 13:48:36 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_execute(char *command_argv, char **envp, char *command_path)
{
	char	**cmd;
	char	*error_msg;
	int		i;

	i = 0;
	if (command_argv[0] == '\0')
		cmd = ft_split("cat", ' ');
	else
		cmd = ft_split(command_argv, ' ');
	if (command_path == NULL)
		execve("/bin/cat", cmd, envp);
	else if (execve(command_path, cmd, envp) == -1)
	{
		error_msg = ft_strjoin(cmd[0], " command not found:");
		perror(error_msg);
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

	if (ft_strlen(command) != -1 && command == NULL)
	{
		perror("command1 not valid");
		exit(0);
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

	if (command == NULL)
	{
		perror("command2 not valid hehe");
		exit(127);
	}
	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1 || dup2(fd, 1) == -1 || dup2(fdp[0], 0) == -1)
	{
		perror("out-file failed");
		exit(0);
	}
	close(fdp[1]);
	ft_execute(argv[3], envp, command);
}

void	waiting(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 0)
			exit(WEXITSTATUS(status));
	}
}

void	pipex(char *argv[], char *envp[])
{
	int	pid1;
	int	pid2;
	int	fdp[2];

	if (pipe(fdp) < 0)
		perror("pipe error");
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("forking gone wrong");
		exit(3);
	}
	if (pid1 == 0)
		child1(argv, fdp, envp, get_command(ft_split(argv[2], ' '), envp));
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			perror("forking gone wrong");
		if (pid2 == 0)
			child2(argv, fdp, envp, get_command(ft_split(argv[3], ' '), envp));
		wait(NULL);
	}
	(close(fdp[0]), close(fdp[1]));
	waiting();
}
