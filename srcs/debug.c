/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:32:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/19 17:05:29 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (tmp->type == INFILE)
			ft_printf("INFILE ");
		else if (tmp->type == OUTFILE)
			ft_printf("OUTFILE ");
		else if (tmp->type == INFILE_NEXT)
			ft_printf("INFILE_NEXT ");
		else if (tmp->type == OUTFILE_NEXT)
			ft_printf("OUTFILE_NEXT ");
		else if (tmp->type == HEREDOC)
			ft_printf("HEREDOC_NEXT ");
		else if (tmp->type == HEREDOC_LIMITER)
			ft_printf("HEREDOC_LIMITER ");
		else if (tmp->type == APPEND_NEXT)
			ft_printf("APPEND_NEXT ");
		else if (tmp->type == APPEND)
			ft_printf("APPEND ");
		tmp = tmp->next;
	}
	ft_putchar_fd('\n', 1);
}
