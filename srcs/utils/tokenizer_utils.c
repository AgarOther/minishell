/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:44:56 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 01:42:41 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_list_remove_if(char *var, t_list *current, int free_var)
{
	t_list	*head;
	t_list	*prev;

	head = current;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(var, current->str,
			ft_strcharindex(current->str, '=') + 1))
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
		if (!quote && (ft_isspace(str[i]) || is_token(str[i])))
			break ;
	}
	return (i);
}

t_type	get_type(char *str)
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
