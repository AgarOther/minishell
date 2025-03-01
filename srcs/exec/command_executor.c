/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/01 22:32:50 by scraeyme         ###   ########.fr       */
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

static void	free_forkit(char *path, char **cmd, t_data *data, int exit_code)
{
	if (exit_code == 126)
		ft_putendl_fd("Error: Is a directory.", 2);
	else if (exit_code == 127)
	{
		ft_putstr_fd("Error: Command failed to execute: ", 2);
		ft_putendl_fd(cmd[0], 2);
	}
	if (path)
		free(path);
	ft_tabfree(cmd, ft_tablen(cmd));
	free_data(data, 1);
	exit(exit_code);
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
		if (path && path[0] == '.' && is_directory(path))
			free_forkit(path, cmd, data, 126);
		cmd = delete_cmd_quotes(cmd);
		if (ft_execve(path, cmd, data, raw_cmd) == -1)
			free_forkit(path, cmd, data, 127);
	}
	close_fd(data);
	return (pid);
}
