/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/21 14:55:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_invalid_syntax(t_data *data)
{
	t_token	*tokens;
	t_token	*prev;
	int		size;

	tokens = data->tokens;
	prev = NULL;
	size = ft_tokensize(tokens);
	if (size == 1 && tokens->type == PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type == UNDEFINED)
			return (1);
		else if (!tokens->next && tokens->type == PIPE)
			return (1);
		else if (prev && prev->type == tokens->type)
			return (1);
		prev = tokens;
		tokens = tokens->next;
	}
	return (0);
}

int	has_invalid_quotes(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && ((str[i] == '\'') || (str[i] == '\"')))
			quote = str[i];
		if (quote)
		{
			if (str[i] == quote)
				count++;
			if (count == 2)
			{
				count = 0;
				quote = 0;
			}
		}
		i++;
	}
	return (count != 0);
}

void	split_more_cmds(t_data *data, char **cmd, int i)
{
	int pid[data->nb_cmds];
	
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

	i = 0;
	while (i < data->nb_cmds)
	{
		cmd = ft_split(data->cmds[i], ' ');
		if (!ft_strcmp(cmd[0], "cd"))
			ft_cd(data);
		else if (!ft_strcmp(cmd[0], "echo"))
			ft_echo(data, &data->cmds[i][5]);
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
		i++;
	}
	ft_tabfree(cmd, ft_tablen(cmd));
	return (1);
}

t_list	*get_env_as_lst(t_data *data)
{
	t_list	*env;
	char	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (!env || tmp)
	{
		tmp = ft_strdup(data->envp[i]);
		if (!tmp)
			break ;
		if (!env)
			env = ft_lstnew(tmp);
		else
			ft_lstadd_back(&env, ft_lstnew(tmp));
		i++;
	}
	return (env);
}
