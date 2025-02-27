/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:47:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/27 15:48:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_error_code(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

char	*get_cmd_path(char **envp, char *cmd, int i)
{
	char	**paths;
	char	*path;

	if (!access (cmd, X_OK))
		return (ft_strdup(cmd));
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		path = ft_strjoin(paths[i], cmd);
		if (!access(path, X_OK))
		{
			ft_tabfree(paths, i);
			return (path);
		}
		free(path);
	}
	if (paths)
		ft_tabfree(paths, ft_tablen(paths));
	return (NULL);
}

char	*addquotes(char *str)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (!str)
		return (NULL);
	cpy = malloc(ft_strlen(str) + 3);
	cpy[0] = 34;
	while (str[i])
		cpy[j++] = str[i++];
	cpy[j] = 0;
	free(str);
	return (cpy);
}
