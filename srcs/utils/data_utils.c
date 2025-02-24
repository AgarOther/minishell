/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:54:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 00:18:40 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_data *data)
{
	if (data->in > 1)
		close(data->in);
	if (data->out > 1)
		close(data->out);
}

void	free_data(t_data *data, int free_envp)
{
	close_fd(data);
	if (data->out_tmp > 1)
		close(data->out_tmp);
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (data->pipes)
		free_pipes(data);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->input)
		free(data->input);
	if (data->list)
		ft_lstclear(&data->list);
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (free_envp && data->envp)
		ft_tabfree(data->envp, ft_tablen(data->envp));
	if (free_envp)
		free(data);
}

t_data	*fill_data(t_data *data, int i)
{
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
