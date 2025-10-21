/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:55:40 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/21 21:07:31 by sbrochar         ###   ########.fr       */
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
			if (px->pipe_fd[0] != -1)
				close(px->pipe_fd[0]);
			if (px->pipe_fd[1] != -1)
				close(px->pipe_fd[1]);
			waitpid(pid, NULL, 0);
			waitpid(pid2, NULL, 0);
			if (px->paths)
				free_argv(px->paths);
		}
	}
}

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		write(2, "wrong args number\n", 19);
		return ;
	}
	px.pipe_fd[0] = -1;
	px.pipe_fd[1] = -1;
	px.fd[0] = -1;
	px.fd[1] = -1;
	px.infile = argv[1];
	px.cmd1 = argv[2];
	px.cmd2 = argv[3];
	px.outfile = argv[4];
	px.envp = envp;
	px.paths = get_paths(envp);
	if (pipe(px.pipe_fd) == -1)
		return (perror("pipe failed\n"));
	run_child(&px);
}
