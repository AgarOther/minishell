/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/25 15:25:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	global_free(t_data *data)
{
	close_fd(data);
	safe_close(data->out_tmp);
	free_pipes(data);
	return (1);
}

pid_t	forkit(t_data *data, char **cmd, char *to_free)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		free(to_free);
		if (dup2(data->in, STDIN_FILENO) == -1
			|| dup2(data->out, STDOUT_FILENO) == -1)
			return (global_free(data));
		global_free(data);
		path = get_cmd_path(data->envp, cmd[0], -1);
		if (!path || execve(path, cmd, data->envp) == -1)
		{
			if (path)
				free(path);
			ft_tabfree(cmd, ft_tablen(cmd));
			free_data(data, 1);
			exit(127);
		}
	}
	close_fd(data);
	return (pid);
}
