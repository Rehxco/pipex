/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:55:40 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/27 18:29:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanup_parent(t_pipex *px, pid_t pid1, pid_t pid2)
{
	if (px->pipe_fd[0] != -1)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] != -1)
		close(px->pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	if (px->paths)
		free_argv(px->paths);
}

int	run_child(t_pipex *px)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	else if (pid == 0)
		run_cmd1(px->cmd1, px->infile, px);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (perror("fork"), -1);
		else if (pid2 == 0)
			run_cmd2(px->cmd2, px->outfile, px);
		else
			cleanup_parent(px, pid, pid2);
	}
	return (0);
}
