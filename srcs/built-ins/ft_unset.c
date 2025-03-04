/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:49:28 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/05 00:02:40 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data **data, char *var)
{
	t_list		*current;

	(*data)->nb_cmds--;
	if (!var)
		return ;
	else if (!ft_stralnum(var))
		return ;
	var = ft_strjoin(var, "=");
	current = get_env_as_lst(*data);
	current = ft_list_remove_if(var, current, 1);
	update_env(current, *data);
	ft_lstclear(&current);
	(*data)->exit_code = 0;
}
