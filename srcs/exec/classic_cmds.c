/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/25 00:24:29 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	forkit(t_data *data, char **cmd, char *to_free)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(data->in, STDIN_FILENO) == -1 ||
				dup2(data->out, STDOUT_FILENO) == -1)
			return (1);
		close_fd(data);
		close(data->out_tmp);
		free(to_free);
		free_pipes(data);
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
