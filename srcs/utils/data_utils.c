/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:54:11 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 16:42:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_data *data)
{
	safe_close(data->in);
	safe_close(data->out);
}

static void	free_null(pid_t	**pids)
{
	free(*pids);
	*pids = NULL;
}

int	free_data(t_data *data, int free_envp)
{
	int	exit_code;

	exit_code = data->exit_code;
	close_fd(data);
	safe_close(data->out_tmp);
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (data->pipes)
		free_pipes(data);
	if (data->pids)
		free_null(&data->pids);
	if (data->input)
		free(data->input);
	if (data->list)
		ft_lstclear(&data->list);
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (free_envp && data->envp)
		ft_tabfree(data->envp, ft_tablen(data->envp));
	if (free_envp)
	{
		free(data);
		rl_clear_history();
	}
	return (exit_code);
}

t_data	*fill_data(t_data *data)
{
	int	i;

	i = 0;
	data->pids = ft_calloc(sizeof(pid_t), data->nb_cmds);
	if (!data->pids)
	{
		free_data(data, 0);
		return (NULL);
	}
	if (data->nb_cmds > 1)
	{
		data->pipes = malloc(sizeof(int *) * data->nb_cmds - 1);
		while (i < data->nb_cmds - 1)
		{
			data->pipes[i] = malloc(sizeof(int) * 2);
			if (pipe(data->pipes[i]) == -1)
			{
				ft_putendl_fd("Error opening pipes. Aborting.", 2);
				ft_tabfree((char **)data->pipes, i);
				return (NULL);
			}
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
	data->exit_code = 0;
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
