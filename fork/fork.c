/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:58:26 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/29 23:21:18 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	clean_exit_child(t_pipex *px, char **argv, int code)
{
	if (argv)
		free_argv(argv);
	if (px->paths)
		free_argv(px->paths);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	exit(code);
}

void	run_cmd1(char *cmd, char *file_in, t_pipex *px)
{
	char	**argv;
	int		fd_in;

	argv = build_cmd(cmd, px->paths);
	if (!argv)
		cmd_not_found(cmd, px);
	fd_in = open(file_in, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open file_in");
		clean_exit_child(px, argv, 1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		close(fd_in);
		clean_exit_child(px, argv, 1);
	}
	close(fd_in);
	close(px->pipe_fd[0]);
	if (dup2(px->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe write");
		clean_exit_child(px, argv, 1);
	}
	close(px->pipe_fd[1]);
	execve(argv[0], argv, px->envp);
	perror("execve");
	clean_exit_child(px, argv, EXIT_FAILURE);
}

void	run_cmd2(char *cmd, char *file_out, t_pipex *px)
{
	char	**argv;
	int		fd_out;

	argv = build_cmd(cmd, px->paths);
	if (!argv)
		cmd_not_found(cmd, px);
	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open file_out");
		clean_exit_child(px, argv, 1);
	}
	close(px->pipe_fd[1]);
	if (dup2(px->pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 pipe read");
		close(fd_out);
		clean_exit_child(px, argv, 1);
	}
	close(px->pipe_fd[0]);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		close(fd_out);
		clean_exit_child(px, argv, 1);
	}
	close(fd_out);
	execve(argv[0], argv, px->envp);
	perror("execve");
	clean_exit_child(px, argv, EXIT_FAILURE);
}
