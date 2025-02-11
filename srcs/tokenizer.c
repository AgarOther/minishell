/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:50:54 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 15:43:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*iterate_input(char **input, t_token *tokens, int i)
{
	t_token	*new;
	int		has_piped;

	while (input[i])
	{
		if ((!i || has_piped) && !(ft_strchr(input[i], '|')
				&& ft_strlen(input[i]) == 1))
		{
			has_piped = 0;
			new = ft_newtoken(input[i], COMMAND);
		}
		else if (ft_strlen(input[i]) == 1 && ft_strchr(input[i], '|'))
		{
			has_piped = 1;
			new = ft_newtoken(input[i], PIPE);
		}
		else
			new = ft_newtoken(input[i], ARG);
		if (!tokens)
			tokens = new;
		else
			ft_tokenadd_back(&tokens, new);
		i++;
	}
	return (tokens);
}

static void	iterate_for_spaces(int i, int j, char *src, char *str)
{
	int	len;

	len = ft_strlen(src);
	while (src[i])
	{
		if (src[i] == '|')
		{
			if (i > 0 && !ft_isspace(src[i - 1]))
			{
				str[j] = ' ';
				j++;
			}
		}
		str[j] = src[i];
		j++;
		if (src[i] == '|')
		{
			if (i + 1 < len && !ft_isspace(src[i + 1]))
			{
				str[j] = ' ';
				j++;
			}
		}
		i++;
	}
}

static char	*add_spaces_to_pipes(char *src, int len)
{
	char	*str;

	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	iterate_for_spaces(0, 0, src, str);
	return (str);
}

static char	*fix_pipes(char *str, int len, int i)
{
	int		spaces_needed;
	int		is_quoted;

	spaces_needed = 0;
	is_quoted = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && is_quoted)
			is_quoted = 0;
		else if ((str[i] == '\'' || str[i] == '\"') && !is_quoted)
			is_quoted = 1;
		if (is_quoted)
			continue ;
		if (str[i] == '|')
		{
			if (i > 0 && !ft_isspace(str[i - 1]))
				spaces_needed++;
			if (i + 1 < len && !ft_isspace(str[i + 1]))
				spaces_needed++;
		}
	}
	if (!spaces_needed)
		return (str);
	return (add_spaces_to_pipes(str, len + spaces_needed));
}

t_token	*get_tokens(t_data *data)
{
	t_token	*tokens;
	char	**input;

	tokens = ft_calloc(data->nb_cmds, sizeof(t_token));
	if (!tokens)
		return (NULL);
	data->input = fix_pipes(data->input, ft_strlen(data->input), -1);
	input = ft_split(data->input, ' ');
	if (!input)
	{
		free(tokens);
		return (NULL);
	}
	tokens = NULL;
	tokens = iterate_input(input, tokens, 0);
	return (tokens);
}
