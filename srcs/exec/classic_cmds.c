/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/24 23:01:25 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	forkit(t_data *data, char **cmds, char **to_free)
{
	pid_t	pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == 0)
	{
		cmd = ft_split(cmds[0], ' ');
		path = get_cmd_path(data->envp, cmd[0], -1);
		if (!path || execve(path, cmd, data->envp) == -1)
		{
			if (path)
				free(path);
			ft_tabfree(cmd, ft_tablen(cmd));
			ft_tabfree(to_free, ft_tablen(to_free));
			free_data(data, 1);
			exit(127);
		}
	}
	return (pid);
}

void	closeall(t_data *data)
{
	if (data->fd[0])
		close(data->fd[0]);
	if (data->fd[1])
		close(data->fd[1]);
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
}
