/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:58:26 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/27 18:30:48 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void	open_dup_in(t_pipex *px, char *file, char **cmd)
{
	px->fd[0] = open(file, O_RDONLY);
	if (px->fd[0] == -1)
	{
		perror("open file_in");
		clean_exit_child(px, cmd, 1);
	}
	if (dup2(px->fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		close(px->fd[0]);
		clean_exit_child(px, cmd, 1);
	}
	close(px->fd[0]);
	close(px->pipe_fd[0]);
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe write");
		clean_exit_child(px, cmd, 1);
	}
	close(px->pipe_fd[1]);
}

static void	open_dup_out(t_pipex *px, char *file, char **comm)
{
	px->fd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->fd[1] == -1)
	{
		perror("Open file_out");
		clean_exit_child(px, comm, 1);
	}
	close(px->pipe_fd[1]);
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 pipe read");
		close(px->fd[1]);
		clean_exit_child(px, comm, 1);
	}
	close(px->pipe_fd[0]);
	if (dup2(px->fd[1], STDOUT_FILENO) == -1)
	{
		perror("Dup2 outfile");
		close(px->fd[1]);
		clean_exit_child(px, comm, 1);
	}
	close(px->fd[1]);
}

void	clean_exit_child(t_pipex *px, char **argv, int code)
{
	if (argv)
		free_argv(argv);
	if (px->paths)
		free_argv(px->paths);
	if (px->pipe_fd[0] != -1)
		close(px->pipe_fd[0]);
	if (px->pipe_fd[1] != -1)
		close(px->pipe_fd[1]);
	if (px->fd[0] != -1)
		close(px->fd[0]);
	if (px->fd[1] != -1)
		close(px->fd[1]);
	exit(code);
}

void	run_cmd1(char *cmd, char *file_in, t_pipex *px)
{
	px->final_cmd1 = build_cmd(cmd, px->paths);
	if (!px->final_cmd1)
	{
		write(2, "Commands unknown\n", 18);
		clean_exit_child(px, px->final_cmd1, EXIT_FAILURE);
	}
	open_dup_in(px, file_in, px->final_cmd1);
	execve(px->final_cmd1[0], px->final_cmd1, px->envp);
	write(2, "Execve failed\n", 15);
	clean_exit_child(px, px->final_cmd1, EXIT_FAILURE);
}

void	run_cmd2(char *cmd, char *file_out, t_pipex *px)
{
	px->final_cmd2 = build_cmd(cmd, px->paths);
	if (!px->final_cmd2)
	{
		write(2, "Commands unknown\n", 18);
		free_argv(px->final_cmd2);
		px->fd[1] = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		clean_exit_child(px, px->final_cmd2, EXIT_FAILURE);
	}
	open_dup_out(px, file_out, px->final_cmd2);
	execve(px->final_cmd2[0], px->final_cmd2, px->envp);
	perror("Execve");
	clean_exit_child(px, px->final_cmd2, EXIT_FAILURE);
}
