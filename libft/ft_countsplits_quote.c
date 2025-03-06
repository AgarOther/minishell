/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countsplits_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:17:21 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 21:17:33 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	handle_quotes(char c, int *quote)
{
	if (c == '\"' || c == '\'')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}

int	ft_countsplits_quote(const char *str, char c)
{
	int	i;
	int	strs;
	int	is_spaced;
	int	quote;

	i = 0;
	strs = 0;
	is_spaced = 1;
	quote = 0;
	while (str[i])
	{
		handle_quotes(str[i], &quote);
		if (is_spaced && str[i] != c && !quote)
		{
			is_spaced = 0;
			strs++;
		}
		else if (!is_spaced && str[i] == c && !quote)
			is_spaced = 1;
		i++;
	}
	return (strs);
}
