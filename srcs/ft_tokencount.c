/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencount.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:40 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 20:59:15 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tokencount(t_token *tokens, t_TYPE type)
{
	int	nb_cmds;

	nb_cmds = 0;
	while (tokens)
	{
		if (tokens->type == type)
			nb_cmds++;
		tokens = tokens->next;
	}
	return (nb_cmds);
}
