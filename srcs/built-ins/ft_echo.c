/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/03 23:32:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_option(char *str, int *i)
{
	int	tmp;

	if (!str || !str[0] || ft_strlen(str) < 3 || ft_strncmp(&str[1], "-n", 2))
		return (0);
	tmp = 2;
	while (str[tmp] && str[tmp] == 'n')
		tmp++;
	if (!str[tmp] || ft_isspace(str[tmp]))
		*i = tmp + 1;
	else
		return (0);
	return (1);
}

void	ft_echo(t_data **data, char *str, int i)
{
	int	has_newline;
	int	quote;

	if (has_option(str, &i))
		has_newline = 0;
	else
		has_newline = 1;
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
