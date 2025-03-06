/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/04 23:02:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_alloc_size(char *str)
{
	int	quote;
	int	i;
	int	size;

	quote = 0;
	i = 0;
	size = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			size++;
		i++;
	}
	return (size);
}

char	*delete_quotes(char *str, int needs_free)
{
	int		quote;
	int		i;
	int		j;
	char	*new;

	quote = 0;
	i = 0;
	j = 0;
	new = ft_calloc(get_alloc_size(str) + 1, 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	if (needs_free)
		free(str);
	return (new);
}

int	has_invalid_syntax(t_data *data)
{
	t_token	*tokens;

	tokens = data->tokens;
	if (tokens->type == PIPE)
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
