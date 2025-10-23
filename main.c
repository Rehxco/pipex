/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:56:40 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/23 21:58:59 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		write(2, "wrong args number\n", 19);
		return (1);
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
		return (perror("pipe failed\n"), 1);
	if (run_child(&px) == -1)
		return (1);
	return (0);
}
