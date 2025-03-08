/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:15:29 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 16:08:15 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipes(t_data **data, char **cmd, char *raw_cmd, t_token *token)
{
	if ((*data)->nb_cmds < 2)
	{
		if (set_file_descriptors(data, token) && (*data)->nb_cmds)
			(*data)->pids[(*data)->cmd_count] = forkit(*data, cmd, raw_cmd);
		else
			close_fd(*data);
		return ;
	}
	else if ((*data)->cmd_count == 0)
		(*data)->out = (*data)->pipes[0][1];
	else if ((*data)->cmd_count < (*data)->nb_cmds - 1)
	{
		(*data)->in = (*data)->pipes[(*data)->cmd_count - 1][0];
		(*data)->out = (*data)->pipes[(*data)->cmd_count][1];
	}
	else
	{
		(*data)->in = (*data)->pipes[(*data)->cmd_count - 1][0];
		(*data)->out = (*data)->out_tmp;
	}
	if (set_file_descriptors(data, token) && (*data)->nb_cmds)
		(*data)->pids[(*data)->cmd_count] = forkit(*data, cmd, raw_cmd);
	else
		close_fd(*data);
}

static void	execute_command(t_data *data, char *raw_cmd, t_token *tokens)
{
	char		**cmd;

	data->raw_cmd = raw_cmd;
	cmd = ft_split_quote(raw_cmd, ' ');
	if (cmd && !ft_strcmp(cmd[0], "exit"))
		ft_exit(&data, cmd, 0, 0);
	else if (cmd && !ft_strcmp(cmd[0], "cd"))
		ft_cd(&data, cmd, NULL);
	else if (cmd && !ft_strcmp(cmd[0], "unset"))
		ft_unset(&data, &cmd[1]);
	else if (cmd && !ft_strcmp(cmd[0], "export") && cmd[1])
		ft_export(&data, &cmd[1]);
	else
		set_pipes(&data, cmd, raw_cmd, tokens);
	if (cmd)
		ft_tabfree(cmd, ft_tablen(cmd));
	if (raw_cmd)
		free(raw_cmd);
	data->cmd_count++;
}

static char	*construct_command(t_token *tokens)
{
	char	*command;

	while (tokens && tokens->type != COMMAND)
		tokens = tokens->next;
	if (!tokens)
		return (NULL);
	command = ft_strdup(tokens->arg);
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == INFILE || tokens->type == HEREDOC
			|| tokens->type == APPENDFILE || tokens->type == OUTFILE
			|| tokens->type == HEREDOC_QUOTE)
		{
			tokens = tokens->next;
			continue ;
		}
		else if (tokens->type == PIPE)
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
	status = 0;
	while (i < data->nb_cmds)
	{
		waitpid(data->pids[i], &status, 0);
		i++;
	}
	if (data->pipeline_error)
		return (data->pipeline_error);
	return (get_error_code(status));
}

void	process_tokens(t_data **data)
{
	char	*cmd;
	t_token	*tokens;

	tokens = (*data)->tokens;
	while (tokens && !g_signal)
	{
		if (tokens->type == COMMAND || tokens->type == HEREDOC
			|| tokens->type == INFILE || tokens->type == OUTFILE
			|| tokens->type == APPENDFILE || tokens->type == HEREDOC_QUOTE)
		{
			(*data)->pipeline_error = 0;
			cmd = construct_command(tokens);
			if (cmd && !ft_strcmp(cmd, "."))
			{
				ft_strerror(data, 2, INVALID_PARAM);
				(*data)->pipeline_error = 2;
			}
			execute_command((*data), cmd, tokens);
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	(*data)->exit_code = wait_children(*data);
}
