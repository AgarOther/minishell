/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 15:23:16 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_alloc_size(t_data *data, char *command, int i, int value)
{
	char	*tmp;
	char	*var;

	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] && !ft_isspace(command[i + 1]))
		{
			tmp = ft_substr(&command[i], 1, ft_strcharindex(&command[i], ' '));
			tmp = ft_strjoin_free(tmp, "=");
			var = grep_var_as_string(data->envp, tmp);
			if (var)
			{
				i += ft_strcharindex(&command[i], ' ') - 1;
				value += ft_strlen(var);
			}
			else
				value++;
			if (tmp)
				free(tmp);
		}
		else
			value++;
		i++;
	}
	return (value);
}

static char	*expand_command(t_data *data, char *command)
{

}

void	get_parsed_input(t_data **data, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	(*data)->nb_cmds = ft_tokencount(tokens, COMMAND);
	(*data)->input = expand_command(*data, (*data)->input);
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
