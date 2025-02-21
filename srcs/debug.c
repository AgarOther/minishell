/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:32:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/21 14:36:04 by scraeyme         ###   ########.fr       */
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
		else if (tmp->type == HEREDOC)
			ft_printf("HEREDOC ");
		else if (tmp->type == APPENDFILE)
			ft_printf("APPENDFILE ");
		else if (tmp->type == UNDEFINED)
			ft_printf("UNDEFINED ");
		tmp = tmp->next;
	}
	ft_putchar_fd('\n', 1);
}
