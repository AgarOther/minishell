/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:44:56 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/01 20:56:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filepath(int cmd_count)
{
	char	*filepath;
	char	*count;

	count = ft_itoa(cmd_count);
	if (!count)
		return (NULL);
	filepath = ft_strjoin(TMP_FILEPATH, count);
	free(count);
	return (filepath);
}

t_list	*ft_list_remove_if(char *var, t_list *current, int free_var)
{
	t_list	*head;
	t_list	*prev;

	head = current;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(var, current->str, ft_strcharindex(current->str, '=')))
		{
			if (prev == NULL)
				head = current->next;
			else
				prev->next = current->next;
			free(current->str);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	if (free_var)
		free(var);
	return (head);
}

int	is_token(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	get_token_length(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!quote)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		i++;
		if (!quote && ft_isspace(str[i]))
			break ;
	}
	return (i);
}

t_TYPE	get_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(str, ">>", 2))
		return (APPENDFILE);
	else if (!ft_strncmp(str, ">", 1))
		return (OUTFILE);
	else if (!ft_strncmp(str, "<", 1))
		return (INFILE);
	else if (!ft_strncmp(str, "|", 1))
		return (PIPE);
	else
		return (ARG);
}
