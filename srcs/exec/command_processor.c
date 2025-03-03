/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:15:29 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/03 12:26:11 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipes(t_data **data, char **cmd, char *raw_cmd, t_token *token)
{
	if ((*data)->nb_cmds < 2)
	{
		if (set_file_descriptors(data, token))
			(*data)->pids[(*data)->cmd_count] = forkit(*data, cmd, raw_cmd);
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
	if (set_file_descriptors(data, token))
		(*data)->pids[(*data)->cmd_count] = forkit(*data, cmd, raw_cmd);
}

static void	execute_command(t_data *data, char *raw_cmd, t_token *tokens)
{
	char		**cmd;

	cmd = ft_split_quote(raw_cmd, ' ');
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(&data, cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(&data, cmd, NULL);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(&data, cmd[1]);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(data, ft_strdup(cmd[1]));
	else
	{
		set_pipes(&data, cmd, raw_cmd, tokens);
		data->cmd_count++;
		ft_tabfree(cmd, ft_tablen(cmd));
	}
	free(raw_cmd);
}

static char	*construct_command(t_token *tokens)
{
	char	*command;

	while (tokens && tokens->type != COMMAND)
		tokens = tokens->next;
	command = ft_strdup(tokens->arg);
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == INFILE || tokens->type == HEREDOC
			|| tokens->type == APPENDFILE || tokens->type == OUTFILE)
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
		if (!data->pids[i])
			return (data->exit_code);
		waitpid(data->pids[i], &status, 0);
		i++;
	}
	return (get_error_code(status));
}

void	process_tokens(t_data **data)
{
	char	*cmd;
	t_token	*tokens;

	tokens = (*data)->tokens;
	while (tokens)
	{
		if (tokens->type == COMMAND || tokens->type == HEREDOC
			|| tokens->type == INFILE)
		{
			cmd = construct_command(tokens);
			execute_command((*data), cmd, tokens);
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	(*data)->exit_code = wait_children(*data);
}
