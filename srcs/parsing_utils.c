/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:24:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/13 15:37:16 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_valid_input(t_token *tokens)
{
	if (!tokens || tokens->type != COMMAND)
		return (0);
	while (tokens)
	{
		if (!tokens->next && tokens->type == PIPE)
			return (0);
		else if (tokens->next && tokens->type == PIPE
			&& tokens->next->type == PIPE)
			return (0);
		tokens = tokens->next;
	}
	return (1);
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
	return (count == 0);
}

void	split_cmds(t_data *data)
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
			ft_echo(&data->cmds[i][5], 1, -1);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_env(data);
		else if (!ft_strcmp(cmd[0], "pwd"))
			ft_pwd(data);
		else if (!ft_strcmp(cmd[0], "exit"))
		{
			ft_tabfree(cmd, ft_tablen(cmd));
			ft_exit(data);
		}
		else if (!ft_strcmp(cmd[0], "unset"))
			ft_unset(data, cmd[1]);
		i++;
	}
	ft_tabfree(cmd, ft_tablen(cmd));
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
