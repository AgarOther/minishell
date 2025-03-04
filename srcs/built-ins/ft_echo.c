/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/05 00:09:08 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_option(char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!ft_strncmp(&str[i], "-n", 2))
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if (!str[i] || ft_isspace(str[i]))
		{
			*index = *index + i + (str[i] != 0);
			return (1);
		}
	}
	return (0);
}

void	ft_echo(t_data **data, char *str, int i)
{
	int	has_newline;
	int	quote;

	while (has_option(&str[i], &i))
		;
	has_newline = (i == 0);
	quote = 0;
	while (str[i])
	{
		if ((!quote && (str[i] == '\'' || str[i] == '\"'))
			|| (quote && str[i] == quote))
		{
			if (!quote)
				quote = str[i];
			else
				quote = 0;
		}
		else if (i)
			write(1, &str[i], 1);
		i++;
	}
	if (!str || has_newline)
		ft_putchar_fd('\n', 1);
	(*data)->exit_code = 0;
}
