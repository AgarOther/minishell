/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:50:54 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/01 18:46:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_command_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *tokens;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type != PIPE && ((!prev && tmp->type == ARG)
				|| (prev && prev->type != ARG && prev->type != COMMAND)))
		{
			if (tmp->type != INFILE && tmp->type != OUTFILE
				&& tmp->type != APPENDFILE && tmp->type != HEREDOC)
			{
				if (!prev || (prev && prev->type != INFILE
					&& prev->type != HEREDOC))
					tmp->type = COMMAND;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static t_token	*get_token(char *str, int *i, int *len, char *tmp)
{
	t_TYPE	type;
	t_token	*new;
	int		token_len;
	int		is_allocable;

	type = get_type(str);
	if (type != PIPE)
	{
		while ((is_token(str[*i]) || ft_isspace(str[*i])) && str[*i])
			*i = *i + 1;
		token_len = get_token_length(&str[*i], 0);
		*len = token_len;
		if (!token_len)
			type = UNDEFINED;
		tmp = ft_substr(&str[*i], 0, *len);
		is_allocable = 0;
	}
	else
	{
		*len = 1;
		tmp = "|";
		is_allocable = 1;
	}
	new = ft_newtoken(tmp, type, is_allocable);
	return (new);
}

static int	tokenize(t_token **tokens, char *str, int is_quoted)
{
	t_token	*new;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = NULL;
	if (!is_quoted && is_token(str[i]))
		new = get_token(str, &i, &len, tmp);
	else
	{
		len = get_token_length(str, is_quoted);
		tmp = ft_substr(str, 0, len);
		new = ft_newtoken(tmp, ARG, 1);
		free(tmp);
	}
	if (!*tokens)
		*tokens = new;
	else
		ft_tokenadd_back(tokens, new);
	return (len + i);
}

void	get_tokens(t_data **data)
{
	t_token	*tokens;
	char	*input;
	int		i;
	char	quote;

	input = (*data)->input;
	quote = 0;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i += tokenize(&tokens, &input[i], quote);
	}
	set_command_tokens(&tokens);
	(*data)->tokens = tokens;
}
