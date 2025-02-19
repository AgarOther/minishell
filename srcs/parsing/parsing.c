/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/19 17:05:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_parsed_input(t_data **data, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	(*data)->nb_cmds = ft_tokencount(tokens, COMMAND);
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
			(*data)->cmds[i] = ft_strjoin_free((*data)->cmds[i], tmp->arg);
		if (tmp->type != PIPE && tmp->next)
			(*data)->cmds[i] = ft_strjoin_free((*data)->cmds[i], " ");
		tmp = tmp->next;
	}
}
