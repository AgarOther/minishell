/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:35:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/11 09:35:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(char *str, char c, int quote)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while ((str[i] != c || quote) && str[i])
	{
		if (i && str[i] == quote)
			quote = 0;
		chars++;
		i++;
	}
	return (chars);
}

static void	free_all(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**fill_tab(char **tab, char *str, char c, int i)
{
	int	j;
	int	quote;
	int	is_spaced;

	j = 0;
	quote = 0;
	is_spaced = 1;
	while (str[++i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (is_spaced && str[i] != c)
		{
			tab[j] = ft_calloc(count_char(&str[i], c, quote) + 1, 1);
			if (!tab[j])
			{
				free_all(tab, j);
				return (NULL);
			}
			ft_strlcpy(tab[j++], &str[i], count_char(&str[i], c, quote) + 1);
			while (str[i + 1] && quote)
			{
				if (str[i + 1] == quote)
					quote = 0;
				i++;
			}
			is_spaced = 0;
		}
		else if (!is_spaced && str[i] == c)
			is_spaced = 1;
	}
	return (tab);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(sizeof(char *) * (ft_countsplits((char *)s, c) + 1), 1);
	if (!tab)
		return (NULL);
	tab = fill_tab(tab, (char *)s, c, -1);
	return (tab);
}
