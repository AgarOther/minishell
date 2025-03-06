/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/06 16:58:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_close(int fd)
{
	if (fd > 1)
		close(fd);
}

void	update_env(t_list *lst, t_data **data)
{
	size_t	i;

	i = 0;
	ft_tabfree((*data)->envp, ft_tablen((*data)->envp));
	(*data)->envp = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!(*data)->envp)
		return ;
	while (lst)
	{
		if ((*data)->envp[i] != lst->str)
			(*data)->envp[i] = ft_strdup(lst->str);
		lst = lst->next;
		i++;
	}
	(*data)->envp[i] = 0;
}

void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->nb_cmds)
		return ;
	while (i < data->nb_cmds - 1)
	{
		if (data->pipes && data->pipes[i])
		{
			if (data->pipes[i][0] >= 0)
				close(data->pipes[i][0]);
			if (data->pipes[i][1] >= 0)
				close(data->pipes[i][1]);
			free(data->pipes[i]);
		}
		i++;
	}
	if (data->pipes)
		free(data->pipes);
	data->pipes = NULL;
}

char	*grep_var_as_string(char **envp, char *to_grep)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(to_grep);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_grep, len) == 0)
			return (&envp[i][len]);
		i++;
	}
	return (NULL);
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
