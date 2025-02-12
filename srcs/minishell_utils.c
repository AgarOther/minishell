/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/12 20:05:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_data(t_data *data, int free_envp)
{
	int	i;

	if (data->cmds)
		ft_tabfree(data->cmds, ft_tablen(data->cmds));
	if (data->tokens)
		ft_tokenclear(&data->tokens);
	if (free_envp && data->envp)
		ft_tabfree(data->envp, ft_tablen(data->envp));
	if (data->pipes)
	{
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

	paths = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], to_grep, ft_strlen(to_grep)) == 0)
		{
			paths = ft_split(&envp[i][ft_strlen(to_grep)], ':');
			break ;
		}
	}
	return (paths);
}
