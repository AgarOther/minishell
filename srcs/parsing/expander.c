/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:21:42 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 15:39:05 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_sepindex(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	return (i);
}

static void	handle_values(int *value, char *var, int *i, char *command)
{
	*value += ft_strlen(var);
	*i = *i + get_sepindex(&command[*i + 1]) - 1;
}

static int	get_alloc_size(t_data *data, char *command, int i, int value)
{
	char	*tmp;
	char	*var;

	while (command[++i])
	{
		if (command[i] == '$' && command[i + 1] && !ft_isspace(command[i + 1]))
		{
			if (is_exit_code(&command[i]))
				value += ft_intlen(data->exit_code);
			else
			{
				tmp = ft_substr(&command[i], 1, get_sepindex(&command[i + 1]));
				tmp = ft_strjoin_free(tmp, "=");
				if (tmp)
				{
					var = grep_var_as_string(data->envp, tmp);
					free(tmp);
					if (var)
						handle_values(&value, var, &i, command);
				}
			}
		}
		value++;
	}
	return (value);
}

static int	get_expanded(t_data *data, char *value, char *new)
{
	char	*var;
	char	*tmp;
	int		is_alloc;
	int		len;

	is_alloc = 0;
	tmp = ft_substr(value, 1, get_sepindex(value + 1));
	tmp = ft_strjoin_free(tmp, "=");
	if (!tmp)
		return (0);
	if (is_exit_code(value))
	{
		var = ft_itoa(data->exit_code);
		is_alloc = 1;
	}
	else
		var = grep_var_as_string(data->envp, tmp);
	free(tmp);
	if (!var)
		return (0);
	len = ft_strlen(var) + ft_strlen(new);
	ft_strlcat(new, var, len + 1);
	if (is_alloc && var)
		free(var);
	return (ft_strlen(var) - 1);
}

char	*expand_command(t_data *data, char *command, int i, int j)
{
	int		quotes[2];
	char	*new;

	quotes[0] = 0;
	quotes[1] = 0;
	new = ft_calloc(get_alloc_size(data, command, -1, 0) + 1, 1);
	if (!new)
		return (NULL);
	while (command[++i])
	{
		if (command[i] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		else if (command[i] == '\"')
			quotes[1] = !quotes[1];
		if (!quotes[0] && command[i] == '$' && command[i] && command[i + 1])
		{
			j += get_expanded(data, &command[i], new);
			i += get_sepindex(&command[i + 1]);
		}
		else
			new[j] = command[i];
		j++;
	}
	free(command);
	return (new);
}
