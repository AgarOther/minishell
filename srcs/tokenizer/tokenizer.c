/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:50:54 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/04 16:40:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token *tmp, t_token *last_cmd)
{
	while (last_cmd->next != tmp)
		last_cmd = last_cmd->next;
	return (last_cmd->type == INFILE || last_cmd->type == HEREDOC);
}

static void	set_command_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*last_cmd;
	t_token	*prev;

	tmp = *tokens;
	prev = NULL;
	last_cmd = NULL;
	while (tmp)
	{
		if (tmp->type != PIPE && ((!prev && tmp->type == ARG)
				|| (prev && prev->type != ARG && prev->type != COMMAND)))
		{
			if ((tmp->type != INFILE && tmp->type != OUTFILE
				&& tmp->type != APPENDFILE && tmp->type != HEREDOC)
				&& (!last_cmd || !is_redirection(tmp, last_cmd))
				&& tmp->type != UNDEFINED)
			{
				tmp->type = COMMAND;
				last_cmd = tmp;
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

static t_token	*get_token(char *str, int *i, int *len, char *tmp)
{
	t_type	type;
	t_token	*new;
	int		token_len;
	int		is_allocable;

	type = get_type(str);
	if (type != PIPE)
	{
		while ((is_token(str[*i]) || ft_isspace(str[*i])) && str[*i])
			*i = *i + 1;
		token_len = get_token_length(&str[*i]);
		*len = token_len;
		if (!token_len || !str[*i])
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
		len = get_token_length(str);
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

void	get_tokens(t_data **data, int i)
{
	t_token	*tokens;
	char	*input;
	char	quote;

	input = (*data)->input;
	quote = 0;
	tokens = NULL;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
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
