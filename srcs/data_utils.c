/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:54:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/12 16:56:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*fill_data(t_data *data, int i)
{
	data->nb_cmds = ft_tablen(data->cmds);
	data->pids = ft_calloc(sizeof(pid_t), data->nb_cmds + 1);
	if (!data->pids)
	{
		free_data(data, 0);
		return (NULL);
	}
	if (data->nb_cmds > 1)
	{
		data->pipes = malloc(sizeof(int *) * (data->nb_cmds - 1));
		while (i < data->nb_cmds - 1)
		{
			data->pipes[i] = malloc(sizeof(int) * 2);
			pipe(data->pipes[i]);
			i++;
		}
	}
	return (data);
}

t_data	*setup_data(char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	data->in = 0;
	data->out = 1;
	if (!data)
		return (NULL);
	data->envp = ft_tabdup(envp, ft_tablen(envp));
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
