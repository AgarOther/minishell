/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:32:59 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/02 13:27:48 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data **data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = *data;
	while (tmp->envp[i] && ft_strncmp(tmp->envp[i], "PWD=", 4))
		i++;
	ft_putendl_fd(&tmp->envp[i][4], 1);
	(*data)->exit_code = 0;
}
