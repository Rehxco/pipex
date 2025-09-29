/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:55:40 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/29 22:45:22 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_child(t_pipex *px)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid == 0)
		run_cmd1(px->cmd1, px->infile, px);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			run_cmd2(px->cmd2, px->outfile, px);
		else
		{
			close(px->pipe_fd[0]);
			close(px->pipe_fd[1]);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
			if (px->paths)
			{
				free_argv(px->paths);
				px->paths = NULL;
			}
		}
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		write(1, "wrong args number\n", 19);
		return ;
	}
	px.infile = argv[1];
	px.cmd1 = argv[2];
	px.cmd2 = argv[3];
	px.outfile = argv[4];
	px.envp = envp;
	px.paths = get_paths(envp);
	if (!px.paths)
	{
		write(2, "PATH not found\n", 15);
		return ;
	}
	if (pipe(px.pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	run_child(&px);
}
