/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:01:41 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 21:27:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable(char c)
{
	return (c != '~' && c != '/' && c != '`' && c != '>' && c != '='
		&& c != ':' && c != ';' && c != '{' && c != '+'
		&& c != '}' && c != '(' && c != ')' && c != '&'
		&& c != '^' && c != '%' && c != '$' && c != '#'
		&& c != '!' && c != '<' && c != ',' && c != '.' && c != 92);
}

int	is_blacklist(char c)
{
	return (c == '-' || c == '~'
		|| c == '/' || c == '*' || c == '`' || c == '>'
		|| c == ':' || c == ';' || c == '{' || c == '+'
		|| c == '}' || c == '(' || c == ')' || c == '&'
		|| c == '^' || c == '%' || c == '$' || c == '#'
		|| c == '@' || c == '!' || c == '<' || c == '?'
		|| c == ',' || c == '.' || c == 92 || c == 32);
}

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

void	unlink_heredocs(t_data *data)
{
	t_token	*tmp;
	int		i;
	char	*filename;

	tmp = data->tokens;
	i = 0;
	while (tmp)
	{
		if (tmp->type == HEREDOC || tmp->type == HEREDOC_QUOTE)
		{
			filename = get_tmp_filepath(i);
			unlink(filename);
			free(filename);
			i++;
		}
		tmp = tmp->next;
	}
}
