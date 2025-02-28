/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/27 15:51:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execve(char *path, char **cmd, t_data *data, char *raw_cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(&raw_cmd[5]);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(data, cmd[1]);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(data, ft_strdup(cmd[1]));
	else
	{
		if (!path)
			return (-1);
		free(raw_cmd);
		return (execve(path, cmd, data->envp));
	}
	free(path);
	exit(data->exit_code);
}

static int	global_free(t_data *data)
{
	close_fd(data);
	safe_close(data->out_tmp);
	free_pipes(data);
	return (1);
}

pid_t	forkit(t_data *data, char **cmd, char *raw_cmd)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(data->in, STDIN_FILENO) == -1
			|| dup2(data->out, STDOUT_FILENO) == -1)
			return (global_free(data));
		global_free(data);
		path = get_cmd_path(data->envp, cmd[0], -1);
		if (ft_execve(path, cmd, data, raw_cmd) == -1)
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
