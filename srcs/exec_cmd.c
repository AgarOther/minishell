/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:31:27 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/07 16:07:34 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		{
			free_path(paths, i);
			return (path);
		}
		free(path);
	}
	free(paths);
	return (NULL);
}

pid_t	forkcmd(t_data *data, char *path, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (dup2(data->in, STDIN_FILENO) < 0
			|| dup2(data->pipes[i], STDOUT_FILENO) < 0)
		{
			// closeall(data);
			return (0);
		}
		// closeall(data);
		if (!path || execve(path, cmd, data->envp) == -1)
		{
			// final_free(data.cmd1, data.cmd2, data.path, data);
			exit(127);
		}
	}
}

void	exec_cmds(t_data *data)
{
	char	**cmd;
	int		i;
	char	**path;

	while (data->cmds[i])
	{
		cmd = ft_split(data->cmds[i], ' ');
		path[i] = get_cmd_path(data->envp, cmd[0], -1);
		data->pids[i] = forkcmd(data, path[i], cmd);
		i++;
	}
}
