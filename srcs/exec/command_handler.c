/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:20:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 16:57:46 by scraeyme         ###   ########.fr       */
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
	free_data(data, 1);
	exit(exit_code);
}

int	ft_execve(char *path, char **cmd, t_data *data, char *raw_cmd)
{
	rl_clear_history();
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(&data, &raw_cmd[4], 0);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(&data);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(&data);
	else
	{
		if (!path)
			return (-1);
		return (execve(path, cmd, data->envp));
	}
	free_and_exit(cmd, data, raw_cmd, path);
	return (0);
}

void	handle_commands(t_data *data)
{
	data->input = expand_command(data, data->input, -1, -1);
	get_tokens(&data, 0);
	if (data->tokens && has_invalid_syntax(data))
		return (ft_strerror(&data, 2, INVALID_SYNTAX));
	else if (data->tokens)
	{
		data->nb_cmds = ft_tokencount(data->tokens, COMMAND);
		data->cmd_count = 0;
		data->in = 0;
		data->out = 1;
		data->out_tmp = 1;
		data->pipeline_error = 0;
		if (data->nb_cmds)
			data = fill_data(data);
		process_tokens(&data);
	}
}
