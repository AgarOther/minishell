/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 15:17:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	has_invalid_quotes(char *str, char quote, char other_quote)
{
	int	i;
	int	found_quote;
	int	found_other_quote;
	
	i = 0;
	found_quote = 0;
	found_other_quote = 0;
	while (str[i])
	{
		if (str[i] == quote && !found_quote)
			found_quote = 1;
		else if (str[i] == other_quote && found_quote && !found_other_quote)
			found_other_quote = 1;
		else if (str[i] == other_quote && found_quote && found_other_quote)
			found_other_quote = 0;
		else if (str[i] == other_quote && found_quote && !found_other_quote)
			return (1);
		else if (str[i] == quote && found_quote)
			return (0);
		i++;
	}
	return (0);
}

int	cmd_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_stroccur(str, '\'') % 2 || ft_stroccur(str, '\"') % 2)
		return (0);
	else if (has_invalid_quotes(str, '\'', '\"') || has_invalid_quotes(str, '\"', '\''))
		return (0);
	return (1);
}
