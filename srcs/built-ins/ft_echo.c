/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 00:21:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_option(char *str, int *index)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str && !ft_strncmp(&str[i], "-n", 2))
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

void	ft_echo(t_data **data, char *str)
{
	int		i;
	int		has_newline;
	char	*tmp;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (has_option(&str[i], &i))
		;
	has_newline = (i < 2);
	tmp = delete_quotes(str, 0, -1);
	if (!tmp)
		return ;
	ft_putstr_fd(&tmp[i], 1);
	if (!tmp || has_newline)
		ft_putchar_fd('\n', 1);
	if (tmp)
		free(tmp);
	(*data)->exit_code = 0;
}
