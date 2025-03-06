/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:14:22 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 21:14:22 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(char *str, char c)
{
	int	i;
	int	chars;
	int	quote;

	i = 0;
	chars = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		chars++;
		i++;
		if (str[i] && str[i] == c && !quote)
			break ;
	}
	return (chars);
}

static char	**free_all(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**fill_tab(char **tab, char *str, char c, int i)
{
	int	j;
	int	is_spaced;
	int	quote;

	j = 0;
	is_spaced = 1;
	quote = 0;
	while (str[++i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (is_spaced && str[i] != c)
		{
			tab[j] = ft_calloc(count_char(&str[i], c) + 1, 1);
			if (!tab[j])
				return (free_all(tab, j));
			ft_strlcpy(tab[j++], &str[i], count_char(&str[i], c) + 1);
			is_spaced = 0;
		}
		else if (!is_spaced && str[i] == c && !quote)
			is_spaced = 1;
	}
	return (tab);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(sizeof(char *) * (ft_countsplits_quote
				((char *)s, c) + 1), 1);
	if (!tab)
		return (NULL);
	tab = fill_tab(tab, (char *)s, c, -1);
	return (tab);
}
