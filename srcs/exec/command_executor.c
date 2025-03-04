/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/04 16:57:42 by scraeyme         ###   ########.fr       */
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
		cmd[i] = delete_quotes(cmd[i], 1);
		i++;
	}
	return (cmd);
}

static void	free_forkit(char *raw_cmd, char **cmd, t_data *data)
{
	int	exit_code;

	if ((errno == ENOENT && ft_strncmp(raw_cmd, "./", 2))
			|| (ft_strchr(raw_cmd, '/') && is_directory(raw_cmd))
			|| (!ft_strncmp(raw_cmd, "./", 2) && !access(raw_cmd, F_OK)
			&& access(raw_cmd, X_OK) == -1))
		exit_code = 126;
	else
		exit_code = 127;
	free(raw_cmd);
	ft_tabfree(cmd, ft_tablen(cmd));
	free_data(data, 1);
	exit(exit_code);
}

pid_t	forkit(t_data *data, char **cmd, char *raw_cmd)
{
	pid_t	pid;
	char	*path;

	if (!raw_cmd)
		return (0);
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
			perror(raw_cmd);
			free_forkit(raw_cmd, cmd, data);
		}
	}
	close_fd(data);
	return (pid);
}
