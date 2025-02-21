/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:47:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 15:59:09 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **envp, char *cmd, int i)
{
	char	**paths;
	char	*path;

	if (!access (cmd, X_OK))
		return (cmd);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(&envp[i][5], ':');
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		path = ft_strjoin(paths[i], cmd);
		if (!access(path, X_OK))
			return (path);
		free(path);
	}
	free(paths);
	return (NULL);
}
