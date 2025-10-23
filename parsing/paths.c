/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:02:33 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/23 21:21:32 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**tab;

	i = 0;
	while (envp[i] && (envp[i][0] != 'P' || envp[i][1] != 'A'
			|| envp[i][2] != 'T' || envp[i][3] != 'H' || envp[i][4] != '='))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	tab = ft_split(envp[i] + 5, ':');
	if (!tab)
		return (free(tab), NULL);
	return (tab);
}

char	*try_path(char *paths, char *cmd)
{
	char	*tmp;
	char	*finalcmd;

	tmp = ft_strjoin(paths, "/");
	if (!tmp)
		return (NULL);
	finalcmd = ft_strjoin(tmp, cmd);
	if (!finalcmd)
	{
		free(tmp);
		return (NULL);
	}
	if (access(finalcmd, X_OK) == 0)
	{
		free(tmp);
		return (finalcmd);
	}
	else
	{
		free(tmp);
		free(finalcmd);
		return (NULL);
	}
}

char	*check_path(char **paths, char *cmd)
{
	int		j;
	char	*res;

	j = 0;
	if (!paths)
		return (NULL);
	while (paths[j])
	{
		res = try_path(paths[j], cmd);
		if (res)
		{
			return (res);
		}
		j++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **paths)
{
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		perror(cmd);
		return (NULL);
	}
	return (check_path(paths, cmd));
}
