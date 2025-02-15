/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/14 23:42:55 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_list *lst, t_data *data)
{
	size_t	i;

	i = 0;
	ft_tabfree(data->envp, ft_tablen(data->envp));
	data->envp = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!data->envp)
		return ;
	while (lst)
	{
		if (data->envp[i] != lst->str)
			data->envp[i] = ft_strdup(lst->str);
		lst = lst->next;
		i++;
	}
	data->envp[i] = 0;
}

static void	free_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmds - 1)
	{
		if (data->pipes[i][0] >= 0)
			close(data->pipes[i][0]);
		if (data->pipes[i][1] >= 0)
			close(data->pipes[i][1]);
		free(data->pipes[i]);
	}
	free(data->pipes);
	data->pipes = NULL;
}

int	free_data(t_data *data, int free_envp)
{
	if (data->cmds)
		ft_tabfree(data->cmds, ft_tablen(data->cmds));
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (free_envp && data->envp)
		ft_tabfree(data->envp, ft_tablen(data->envp));
	if (data->pipes)
		free_pipes(data);
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->input)
		free(data->input);
	if (free_envp)
		free(data);
	return (0);
}

char	**grep_var(char **envp, char *to_grep)
{
	char	**paths;
	int		i;
	int		len;

	paths = NULL;
	i = -1;
	len = ft_strlen(to_grep);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], to_grep, len) == 0)
		{
			paths = ft_split(&envp[i][len], ':');
			break ;
		}
	}
	return (paths);
}
