/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 23:07:50 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data, char *str)
{
	int	has_newline;

	if (!ft_strncmp(str, "-n", 2) && (str[2] == ' ' || str[2] == 0))
		has_newline = 0;
	else
		has_newline = 1;
	ft_putstr_fd(str, data->out);
	if (!str || has_newline)
		ft_putchar_fd('\n', 1);
}
