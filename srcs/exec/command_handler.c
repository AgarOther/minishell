/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:20:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 22:39:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_more_cmds(t_data *data, char **cmd, int i)
{
	int	pid[data->nb_cmds];

	if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(data, cmd[1]);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(data, ft_strdup(cmd[1]));
	else
	{
		pid[i] = forkit(data, data->cmds, cmd);
		waitpid(pid[i], NULL, 0);
	}
}

int	split_cmds(t_data *data)
{
	int		i;
	char	**cmd;

	i = -1;
	while (++i < data->nb_cmds)
	{
		cmd = ft_split(data->cmds[i], ' ');
		if (!ft_strcmp(cmd[0], "cd"))
			ft_cd(data);
		else if (!ft_strcmp(cmd[0], "echo"))
			ft_echo(&data->cmds[i][5]);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_env(data);
		else if (!ft_strcmp(cmd[0], "pwd"))
			ft_pwd(data);
		else if (!ft_strcmp(cmd[0], "exit"))
		{
			ft_tabfree(cmd, ft_tablen(cmd));
			ft_exit(data);
		}
		else
			split_more_cmds(data, cmd, i);
	}
	ft_tabfree(cmd, ft_tablen(cmd));
	return (1);
}

static void	process_tokens(t_data *data)
{
	if (!set_file_descriptors(&data))
		return ;
}

void	handle_commands(t_data *data)
{
	data->input = expand_command(data, data->input, -1, -1);
	get_tokens(&data);
	if (data->tokens && has_invalid_syntax(data))
	{
		print_tokens(data->tokens);
		ft_putendl_fd("Error: Invalid syntax.", 2);
		data->cmds = NULL;
	}
	else if (data->tokens)
	{
		get_parsed_input(&data, data->tokens);
		//print_tokens(data->tokens);
		if (data->nb_cmds)
		{
			data = fill_data(data, 0);
			if (!split_cmds(data))
				ft_putstr_fd("Error: Invalid command:", 2);
		}
	}
	process_tokens(data);
}
