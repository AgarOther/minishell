/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencountpipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:40 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 15:22:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tokencountpipes(t_token *tokens)
{
	int	nb_cmds;

	nb_cmds = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			nb_cmds++;
		tokens = tokens->next;
	}
	return (nb_cmds);
}
