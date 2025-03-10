/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:04 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/09 02:27:45 by scraeyme         ###   ########.fr       */
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

static void	free_forkit(char *raw_cmd, char **cmd, t_data *data, int err_cmd)
{
	int	exit_code;

	if (!err_cmd && ((errno == ENOENT && ft_strncmp(raw_cmd, "./", 2))
			|| ((!ft_strncmp(raw_cmd, "./", 1) || !ft_strncmp(raw_cmd, "/", 1)))
			|| (!ft_strncmp(raw_cmd, "./", 2) && !access(raw_cmd, F_OK)
				&& access(raw_cmd, X_OK) == -1)))
		exit_code = 126;
	else
		exit_code = 127;
	free(raw_cmd);
	ft_tabfree(cmd, ft_tablen(cmd));
	free_data(data, 1);
	exit(exit_code);
}

static void	handle_failure(char *path, char *raw_cmd, t_data *data, char **cmd)
{
	if (path)
	{
		if (!is_directory(path) || !ft_strchr(raw_cmd, '/'))
			ft_putendl_fd(INVALID_COMMAND, 2);
		else
			ft_putendl_fd(IS_DIR, 2);
		free(path);
		free_forkit(raw_cmd, cmd, data, 0);
	}
	else
	{
		if (!access(raw_cmd, F_OK) && access(raw_cmd, X_OK) == -1
			&& raw_cmd[0] == '.')
		{
			ft_putendl_fd(PERM_DENIED, 2);
			free_forkit(raw_cmd, cmd, data, 0);
		}
		else if (access(raw_cmd, F_OK) == -1 && (raw_cmd[0] == '/'
				|| !ft_strncmp(raw_cmd, "./", 2)))
			ft_putendl_fd(NO_SUCH_FILE_DIR, 2);
		else
			ft_putendl_fd(INVALID_COMMAND, 2);
		free_forkit(raw_cmd, cmd, data, 1);
	}
}

pid_t	forkit(t_data *data, char **cmd, char *raw_cmd)
{
	pid_t	pid;
	char	*path;

	prevent_signals();
	if (!raw_cmd)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		signal(SIGINT, handle_forkit_signals);
		signal(SIGQUIT, handle_forkit_signals);
		if (dup2(data->in, STDIN_FILENO) == -1
			|| dup2(data->out, STDOUT_FILENO) == -1)
			return (global_free(data));
		cmd = delete_cmd_quotes(cmd);
		path = get_cmd_path(data->envp, cmd[0], -1, NULL);
		global_free(data);
		if (ft_execve(path, cmd, data, raw_cmd) == -1)
			handle_failure(path, raw_cmd, data, cmd);
	}
	close_fd(data);
	return (pid);
}
