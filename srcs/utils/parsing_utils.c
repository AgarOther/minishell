/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/22 23:35:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_invalid_syntax(t_data *data)
{
	t_token	*tokens;
	int		size;

	tokens = data->tokens;
	size = ft_tokensize(tokens);
	if (size == 1 && tokens->type == PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type == UNDEFINED)
			return (1);
		else if (!tokens->next && tokens->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	has_invalid_quotes(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && ((str[i] == '\'') || (str[i] == '\"')))
			quote = str[i];
		if (quote)
		{
			if (str[i] == quote)
				count++;
			if (count == 2)
			{
				count = 0;
				quote = 0;
			}
		}
		i++;
	}
	return (count != 0);
}

t_list	*get_env_as_lst(t_data *data)
{
	t_list	*env;
	char	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (!env || tmp)
	{
		tmp = ft_strdup(data->envp[i]);
		if (!tmp)
			break ;
		if (!env)
			env = ft_lstnew(tmp);
		else
			ft_lstadd_back(&env, ft_lstnew(tmp));
		i++;
	}
	return (env);
}
