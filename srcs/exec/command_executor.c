/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/06 23:08:26 by scraeyme         ###   ########.fr       */
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
	int		i;
	int		is_printf;
	char	*tmp;

	i = 0;
	is_printf = (ft_strcmp(cmd[0], "printf") == 0);
	while (cmd[i])
	{
		if (is_printf && i && cmd[i] && cmd[i][0] == '$'
			&& (cmd[i][1] == '\"' || cmd[i][1] == '\''))
		{
			tmp = ft_substr(cmd[i], 1, ft_strlen(cmd[i]));
			free(cmd[i]);
			cmd[i] = tmp;
		}
		cmd[i] = delete_quotes(cmd[i], 1, -1);
		i++;
	}
	return (cmd);
}

static void	free_forkit(char *raw_cmd, char **cmd, t_data *data)
{
	int	exit_code;

	if ((errno == ENOENT && ft_strncmp(raw_cmd, "./", 2))
		|| ((!ft_strncmp(raw_cmd, "./", 1) || !ft_strncmp(raw_cmd, "/", 1))
			&& is_directory(raw_cmd))
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
		rl_clear_history();
		if (dup2(data->in, STDIN_FILENO) == -1
			|| dup2(data->out, STDOUT_FILENO) == -1)
			return (global_free(data));
		cmd = delete_cmd_quotes(cmd);
		path = get_cmd_path(data->envp, cmd[0], -1, NULL);
		global_free(data);
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
