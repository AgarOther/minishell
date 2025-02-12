/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 16:07:22 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_parsed_input(t_data **data, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	(*data)->nb_cmds = ft_tokencountpipes(tokens);
	(*data)->cmds = ft_calloc((*data)->nb_cmds + 1, sizeof(char *));
	if (!(*data)->cmds)
		return ;
	tmp = tokens;
	i = 0;
	(*data)->cmds[i] = NULL;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		else if (!(*data)->cmds[i])
			(*data)->cmds[i] = ft_strdup(tmp->arg);
		else
			(*data)->cmds[i] = ft_strjoin((*data)->cmds[i], tmp->arg);
		if (tmp->type != PIPE && tmp->next)
			(*data)->cmds[i] = ft_strjoin_free((*data)->cmds[i], " ");
		tmp = tmp->next;
	}
	// ft_tabprint((*data)->cmds, 0);
	// ft_putchar_fd('\n', 1);
}
