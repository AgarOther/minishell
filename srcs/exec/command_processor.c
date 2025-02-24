/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:15:29 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 00:21:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipes(t_data **data, int cmd_count)
{
	if ((*data)->nb_cmds < 2)
		return ;
	else if (cmd_count == 0)
		(*data)->out = (*data)->pipes[0][1];
	else if (cmd_count < (*data)->nb_cmds - 1)
	{
		(*data)->in = (*data)->pipes[cmd_count][0];
		(*data)->out = (*data)->pipes[cmd_count + 1][1];
	}
	else
	{
		(*data)->in = (*data)->pipes[cmd_count - 1][0];
		(*data)->out = (*data)->out_tmp;
	}
}

static int	execute_command(t_data *data, char *raw_cmd)
{
	static int	cmd_count = 0;
	char		**cmd;

	cmd = ft_split(raw_cmd, ' ');
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(&raw_cmd[5]);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(data);
	else if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(data, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(data, cmd[1]);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(data, ft_strdup(cmd[1]));
	else
	{
		set_pipes(&data, cmd_count);
		data->pids[cmd_count++] = forkit(data, cmd, raw_cmd);
	}
	ft_tabfree(cmd, ft_tablen(cmd));
	return (1);
}

static char	*construct_command(t_token *tokens)
{
	char	*command;

	command = ft_strdup(tokens->arg);
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->type == APPENDFILE
				|| tokens->type == OUTFILE)
			return (command);
		else
			command = ft_strjoin_free(command, " ");
		command = ft_strjoin_free(command, tokens->arg);
		tokens = tokens->next;
	}
	return (command);
}

static int	wait_children(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_cmds)
		waitpid(data->pids[i++], &status, 0);
	return (status);
}

void	process_tokens(t_data **data)
{
	char	*cmd;
	t_token	*tokens;

	if (!set_file_descriptors(data))
		return ;
	tokens = (*data)->tokens;
	while (tokens)
	{
		if (tokens->type == COMMAND)
		{
			cmd = construct_command(tokens);
			execute_command((*data), cmd);
			free(cmd);
			while (tokens && tokens->type != PIPE && tokens->type != APPENDFILE
				&& tokens->type != OUTFILE)
				tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	(*data)->exit_code = wait_children(*data);
}
