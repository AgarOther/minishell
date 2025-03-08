/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:49:28 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/07 23:55:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data **data, char **vars)
{
	t_list		*current;
	int			i;

	i = -1;
	while (vars && vars[++i])
	{
		if (!vars[i])
			continue ;
		else if (vars[i] && vars[i][0] == '-' && vars[i][1])
		{
			ft_strerror(data, 2, INVALID_PARAM);
			continue ;
		}
		else if (!ft_stralnum(vars[i]))
			continue ;
		vars[i] = ft_strjoin_free(vars[i], "=");
		current = get_env_as_lst(*data);
		current = ft_list_remove_if(vars[i], current, 0);
		update_env(current, data);
		ft_lstclear(&current);
		(*data)->exit_code = 0;
	}
}
