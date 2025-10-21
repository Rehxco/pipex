/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:04:56 by sbrochar          #+#    #+#             */
/*   Updated: 2025/10/21 17:56:10 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	ft_count_words(const char *str, char sep)
{
	int	i;
	int	count;
	int	inword;

	count = 0;
	inword = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != sep && inword == 0)
		{
			count++;
			inword = 1;
		}
		if (str[i] == sep)
			inword = 0;
		i++;
	}
	return (count);
}

static void	ft_free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*ft_fill_word(const char *str, char sep)
{
	int		i;
	int		j;
	int		count;
	char	*new;

	i = 0;
	j = 0;
	count = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] == sep)
	{
		i++;
		j++;
	}
	while (str[j] && str[j] != sep)
	{
		count++;
		j++;
	}
	new = ft_substr(str, i, count);
	if (!new)
		return (NULL);
	return (new);
}

char	**ft_split(char const *str, char sep)
{
	char	**tab;
	int		i;

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * ((ft_count_words(str, sep) + 1)));
	if (!tab)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != sep || *str == '\0')
		{
			tab[i] = ft_fill_word(str, sep);
			if (tab[i] == NULL)
				return (ft_free_all(tab), NULL);
			str = str + ft_strlen(tab[i] + 1);
			i++;
		}
		str++;
	}
	tab[i] = NULL;
	return (tab);
}
