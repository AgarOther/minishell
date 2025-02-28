/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/28 16:58:14 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data **data, char *str, int i)
{
	int	has_newline;
	int	quote;

	if (!ft_strncmp(str, "-n", 2) && (str[2] == ' ' || str[2] == 0))
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
		else
			write(1, &str[i], 1);
		i++;
	}
	if (!str || has_newline)
		ft_putchar_fd('\n', 1);
	(*data)->exit_code = 0;
}
