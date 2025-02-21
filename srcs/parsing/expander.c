/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:21:42 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 23:54:37 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_sep_index(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
	{
		if (str[i] == '$' || ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}

static int	get_alloc_size(t_data *data, char *command, int i, int value)
{
	char	*tmp;
	char	*var;

	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] && !ft_isspace(command[i + 1]))
		{
			tmp = ft_substr(&command[i], 1, get_sep_index(&command[i + 1]));
			tmp = ft_strjoin_free(tmp, "=");
			if (tmp)
			{
				var = grep_var_as_string(data->envp, tmp);
				free(tmp);
				if (var)
				{
					value += ft_strlen(var);
					i += get_sep_index(&command[i + 1]) - 1;
				}
			}
		}
		value++;
		i++;
	}
	return (value);
}

static int	get_expanded(t_data *data, char *value, char *new)
{
	char	*var;
	char	*tmp;
	int		len;

	tmp = ft_substr(value, 1, get_sep_index(value + 1));
	tmp = ft_strjoin_free(tmp, "=");
	ft_printf("TMP is: %s\n", tmp);
	if (!tmp)
		return (0);
	var = grep_var_as_string(data->envp, tmp);
	free(tmp);
	if (!var)
		return (0);
	len = ft_strlcat(new, var, ft_strlen(var) + ft_strlen(new) + 1);
	return (len);
}

char	*expand_command(t_data *data, char *command, int i, int j)
{
	int		is_quoted;
	char	*new;

	is_quoted = 0;
	new = ft_calloc(get_alloc_size(data, command, 0, 0) + 1, 1);
	if (!new)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\'')
			is_quoted = !is_quoted;
		if (!is_quoted && command[i] == '$'
			&& command[i] && command[i + 1])
		{
			j += get_expanded(data, &command[i], new);
			i += get_sep_index(&command[i + 1]);
		}
		else
			new[j] = command[i];
		i++;
		j++;
	}
	free(command);
	return (new);
}
