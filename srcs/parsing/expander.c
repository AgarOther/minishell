/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:21:42 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 21:28:07 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sepindex(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
		i++;
	return (i);
}

static void	handle_values(int *value, char *var, int *i, char *command)
{
	*value += ft_strlen(var);
	*i = *i + get_sepindex(&command[*i + 1]) - 1;
}

int	get_alloc_size(t_data *data, char *command, int i, int value)
{
	char	*tmp;
	char	*var;

	while (command[++i])
	{
		if (command[i] == '$' && command[i + 1] && !ft_isspace(command[i + 1]))
		{
			if (!ft_strncmp(&command[i], "$?", 2))
				value += ft_intlen(data->exit_code) - 1;
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

int	get_expanded(t_data *data, char *value, char *new)
{
	char	*var;
	char	*tmp;
	int		exit_code;

	exit_code = 0;
	tmp = ft_substr(value, 1, get_sepindex(value + 1));
	tmp = ft_strjoin_free(tmp, "=");
	if (!ft_strncmp(value, "$?", 2))
	{
		var = ft_itoa(data->exit_code);
		exit_code = ft_strlen(var);
	}
	else
		var = grep_var_as_string(data->envp, tmp);
	free(tmp);
	if (!var)
		return (-1);
	new = ft_strcat(new, var);
	if (exit_code && var)
	{
		free(var);
		return (exit_code - 1);
	}
	return (ft_strlen(var) - 1);
}

char	*expand_command(t_data *data, char *command, int i, int j)
{
	int		quotes[2];
	char	*new;

	quotes[0] = 0;
	quotes[1] = 0;
	new = ft_calloc(get_alloc_size(data, command, -1, 0) + 1, 1);
	while (new && command[++i])
	{
		if (command[i] == '\'' && !quotes[1])
			quotes[0] = !quotes[0];
		else if (command[i] == '\"' && !quotes[0])
			quotes[1] = !quotes[1];
		j++;
		if (!quotes[0] && command[i] == '$' && command[i + 1]
			&& !ft_isspace(command[i + 1]) && is_expandable(command[i + 1])
			&& command[i + 1] != '\'' && command[i + 1] != '\"')
		{
			j += get_expanded(data, &command[i], new);
			i += get_sepindex(&command[i + 1]);
		}
		else
			new[j] = command[i];
	}
	free(command);
	return (new);
}
