/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:50:54 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 16:09:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*iterate_input(char **input, int i, int has_piped)
{
	t_token	*new;
	t_token	*tokens;
	int		file_index;
	int		here_doc;
	int		append;

	tokens = NULL;
	file_index = 0;
	here_doc = 0;
	append = 0;
	while (input[++i])
	{
		if (!ft_strcmp(input[i], "|"))
		{
			has_piped = 1;
			new = ft_newtoken(input[i], PIPE);
		}
		else if (!ft_strcmp(input[i], "<"))
		{
			file_index = 1;
			new = ft_newtoken(input[i], INFILE_NEXT);
		}
		else if (file_index == 1)
		{
			file_index = 3;
			new = ft_newtoken(input[i], INFILE);
		}
		else if (!ft_strcmp(input[i], ">"))
		{
			file_index = 2;
			new = ft_newtoken(input[i], OUTFILE_NEXT);
		}
		else if (file_index == 2)
		{
			file_index = 3;
			new = ft_newtoken(input[i], OUTFILE);
		}
		else if (!ft_strcmp(input[i], "<<"))
		{
			here_doc = 1;
			new = ft_newtoken(input[i], HEREDOC);
		}
		else if (here_doc == 1)
		{
			here_doc = 2;
			new = ft_newtoken(input[i], HEREDOC_LIMITER);
		}
		else if (!ft_strcmp(input[i], ">>"))
		{
			append = 1;
			new = ft_newtoken(input[i], APPEND_NEXT);
		}
		else if (append)
		{
			append = 0;
			new = ft_newtoken(input[i], APPEND);
		}
		else if (file_index == 3 || !i || has_piped || here_doc == 2)
		{
			has_piped = 0;
			file_index = 0;
			here_doc = 0;
			new = ft_newtoken(input[i], COMMAND);
		}
		else
			new = ft_newtoken(input[i], ARG);
		if (!tokens)
			tokens = new;
		else
			ft_tokenadd_back(&tokens, new);
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

// On readline
// On expand
// On tokenize
// On check les tokens
// On envoie à l'exec

// Pas besoin d'ajouter les < << > >> en tokens, utiliser ce qu'il y a après directement.
// Les espaces sont à gérer avec un while(isspace()) (en dehors des quotes)

void	get_tokens(t_data **data)
{
	t_token	*tokens;
	char	**input;

	(*data)->input = fix_pipes((*data)->input, ft_strlen((*data)->input), -1); // A tej wallah
	input = ft_split((*data)->input, ' '); // On rigole un max
	if (!input)
		return ;
	tokens = iterate_input(input, -1, 0);
	if (!has_valid_input(tokens))
	{
		print_tokens(tokens);
		ft_putendl_fd("Error: Invalid input.", 2);
		ft_tokenclear(&tokens);
		(*data)->cmds = NULL;
		ft_tabfree(input, ft_tablen(input));
		return ;
	}
	ft_tabfree(input, ft_tablen(input));
	(*data)->tokens = tokens;
}
