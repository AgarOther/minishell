/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:49:28 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/16 15:19:19 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_data *data, char *var)
{
	t_list		*current;

	if (!var)
		return ;
	else if (!ft_stralnum(var))
	{
		ft_putendl_fd("Error: Invalid parameter name.", 2);
		return ;
	}
	var = ft_strjoin(var, "=");
	current = get_env_as_lst(data);
	current = ft_list_remove_if(var, current, 1);
	update_env(current, data);
	ft_lstclear(&current);
}
