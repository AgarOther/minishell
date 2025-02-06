/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/06 14:08:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*grep_env(t_data data, char *to_grep)
{
	int i;
	char	**paths;
	char	*path;

	// if (!access (cmd, X_OK))
	// 	return (cmd);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], to_grep, ft_strlen(to_grep)) == 0)
			paths = ft_split(&envp[i][ft_strlen(to_grep)], ':');
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		path = ft_strjoin(paths[i], cmd);
		if (!access(path, X_OK))
		{
			free_path(paths, i);
			return (path);
		}
		free(path);
	}
	free(paths);
	return (NULL);
}