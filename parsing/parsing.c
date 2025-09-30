/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:52:00 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/30 14:06:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**parse_cmd(char *cmd)
{
	char	**tabs;

	tabs = ft_split(cmd, ' ');
	if (!tabs)
		return (NULL);
	return (tabs);
}

char	**build_cmd(char *cmd, char **paths)
{
	char	**argv;
	char	*tmp;

	argv = parse_cmd(cmd);
	if (!argv)
		return (NULL);
	if (!argv[0])
		return (free(argv), NULL);
	tmp = get_cmd_path(argv[0], paths);
	if (!tmp)
	{
		free_argv(argv);
		return (NULL);
	}
	else
	{
		free(argv[0]);
		argv[0] = tmp;
	}
	return (argv);
}
