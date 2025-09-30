/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:52:26 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/30 14:05:46 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_struct(t_pipex *px)
{
	if (!px)
		return ;
	if (px->final_cmd1)
		free_argv(px->final_cmd1);
	if (px->final_cmd2)
		free_argv(px->final_cmd2);
}
