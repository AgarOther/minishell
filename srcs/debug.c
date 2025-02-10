/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:32:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/10 15:50:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			ft_printf("COMMAND ");
		else if (tmp->type == ARG)
			ft_printf("ARG ");
		else if (tmp->type == PIPE)
			ft_printf("PIPE ");
		tmp = tmp->next;
	}
	ft_putchar_fd('\n', 1);
}
