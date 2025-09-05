/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:59:49 by sbrochar          #+#    #+#             */
/*   Updated: 2025/09/05 15:46:28 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newstr = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		newstr[i] = str2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
