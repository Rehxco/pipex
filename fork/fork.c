/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:58:26 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/11 15:16:40 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	run_cmd1(char *cmd, char *file_in, t_pipex *px)
{
	char	**argv;
	int		fd_in;

	argv = build_cmd(cmd, px->paths);
	if (argv == NULL)
	{
		write(2, "Erreur\n", 7);
		exit(1);
	}
	fd_in = open(file_in, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open file_in");
		exit(1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close(px->pipe_fd[0]);
	dup2(px->pipe_fd[1], STDOUT_FILENO);
	close(px->pipe_fd[1]);
	execve(argv[0], argv, px->envp);
	perror("execve");
	free_argv(argv);
	exit(1);
}

void	run_cmd2(char *cmd, char *file_out, t_pipex *px)
{
	char	**argv;
	int		fd_out;

	argv = build_cmd(cmd, px->paths);
	if (argv == NULL)
	{
		write(2, "Erreur\n", 7);
		exit(1);
	}
	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open file_out");
		exit(1);
	}
	close(px->pipe_fd[1]);
	dup2(px->pipe_fd[0], STDIN_FILENO);
	close(px->pipe_fd[0]);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	execve(argv[0], argv, px->envp);
	perror("execve");
	free_argv(argv);
	exit(1);
}
