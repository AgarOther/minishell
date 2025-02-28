/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:14:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/28 12:02:36 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_data **data, char **cmd)
{
	char			*tmp;
	unsigned char	code;

	code = 0;
	if (ft_tablen(cmd) == 1 || ft_isfilled(cmd[1], ' ', NULL))
		exit((*data)->exit_code);
	if (ft_tablen(cmd) > 2 && ft_stratoiable(cmd[1]))
	{
		ft_strerror(data, 1, TOO_MANY_ARGS);
		code = 1;
		(*data)->exit_code = 1;
		return ;
	}
	tmp = delete_quotes(cmd[1]);
	if (ft_atol(tmp) > LONG_MAX || !ft_stratoiable(tmp))
	{
		ft_strerror(data, 2, NUM_ARG_REQUIRED);
		code = 2;
	}
	if (!code)
		code = (unsigned char)ft_atoi(tmp);
	ft_tabfree(cmd, ft_tablen(cmd));
	free_data(*data, 1);
	free(tmp);
	exit(code);
}
