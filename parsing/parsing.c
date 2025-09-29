/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:52:00 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/29 18:55:00 by sbrochar         ###   ########.fr       */
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

	argv = parse_cmd(cmd);
	if (!argv)
		return (NULL);
	argv[0] = get_cmd_path(argv[0], paths);
	if (argv[0] == NULL)
	{
		free_argv(argv);
		return (NULL);
	}
	return (argv);
}
