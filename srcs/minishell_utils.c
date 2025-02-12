/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/11 16:23:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_data(t_data *data, int free_envp)
{
	int	i;

	if (free_envp && data->envp)
		ft_tabfree(data->envp, ft_tablen(data->envp));
	if (data->cmds)
		ft_tabfree(data->cmds, ft_tablen(data->cmds));
	if (data->pipes)
	{
		i = 0;
		while (i < data->nb_cmds - 1)
		{
			if (data->pipes[i][0] >= 0)
				close(data->pipes[i][0]);
			if (data->pipes[i][1] >= 0)
				close(data->pipes[i][1]);
			free(data->pipes[i]);
			i++;
		}
		free(data->pipes);
	}
	if (data->pids)
		free(data->pids);
	if (data->input)
		free(data->input);
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
