/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/01 18:52:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_exit(char **cmd, t_data *data, char *raw_cmd, char *path)
{
	int	exit_code;

	exit_code = data->exit_code;
	ft_tabfree(cmd, ft_tablen(cmd));
	free(raw_cmd);
	free(path);
	exit_code = data->exit_code;
	free_data(data, 1);
	exit(exit_code);
}

static int	ft_execve(char *path, char **cmd, t_data *data, char *raw_cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(&data, &raw_cmd[5], 0);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(data);
	else
	{
		if (!path)
			return (-1);
		free(raw_cmd);
		return (execve(path, cmd, data->envp));
	}
	free_and_exit(cmd, data, raw_cmd, path);
	return (0);
}

static int	global_free(t_data *data)
{
	close_fd(data);
	safe_close(data->out_tmp);
	free_pipes(data);
	return (1);
}

static char	**delete_cmd_quotes(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = delete_quotes(cmd[i]);
		i++;
	}
	return (cmd);
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
		path = get_cmd_path(data->envp, cmd[0], -1);
		global_free(data);
		cmd = delete_cmd_quotes(cmd);
		if (ft_execve(path, cmd, data, raw_cmd) == -1)
		{
			if (path)
				free(path);
			ft_putstr_fd("Error: Command failed to execute: ", 2);
			ft_putendl_fd(cmd[0], 2);
			ft_tabfree(cmd, ft_tablen(cmd));
			free_data(data, 1);
			exit(127);
		}
	}
	close_fd(data);
	return (pid);
}
