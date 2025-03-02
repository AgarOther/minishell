/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:57:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/02 13:23:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tabprint_if(char **tab, char c, int endl)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (endl && ft_strchr(tab[i], c))
			ft_putendl_fd(tab[i], 1);
		else if (ft_strchr(tab[i], c))
			ft_putstr_fd(tab[i], 1);
		i++;
	}
}

void	ft_env(t_data **data)
{
	ft_tabprint_if((*data)->envp, '=', 1);
	(*data)->exit_code = 0;
}
