/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 16:14:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str)
{
	int	has_newline;
	int	i;
	int	quote;

	if (!ft_strncmp(str, "-n", 2) && (str[2] == ' ' || str[2] == 0))
		has_newline = 0;
	else
		has_newline = 1;
	i = -1;
	quote = 0;
	while (str[++i])
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
	}
	if (!str || has_newline)
		ft_putchar_fd('\n', 1);
}
