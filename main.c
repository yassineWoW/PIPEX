/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yimizare <yimizare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:50:21 by yimizare          #+#    #+#             */
/*   Updated: 2024/03/21 13:48:30 by yimizare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
	{
		perror("input should be like : ./pipex infile cmd1 cmd2 outfile");
		exit(1);
	}
	else
	{
		pipex(argv, envp);
	}
	return (0);
}
