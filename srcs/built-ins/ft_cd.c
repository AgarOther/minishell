/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:38:10 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/02 13:26:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_env(t_data **data, char *env, char *new)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = ft_strlen(env);
	while (ft_strncmp((*data)->envp[i], env, k) != 0)
		i++;
	tmp = ft_strdup((*data)->envp[i]);
	free((*data)->envp[i]);
	(*data)->envp[i] = ft_calloc(k + ft_strlen(new) + 1, 1);
	ft_strlcpy((*data)->envp[i], tmp, ft_strlen(env) + 1);
	free(tmp);
	while (new[j])
	{
		(*data)->envp[i][k] = new[j];
		j++;
		k++;
	}
	(*data)->exit_code = 0;
}

void	ft_cd(t_data **data, char **cmd, char *pwd)
{
	int		len;
	char	*old_pwd;
	char	*path;

	len = ft_tablen(cmd);
	path = delete_quotes(cmd[1]);
	if (len < 2)
		return ;
	else if (len > 2)
	{
		ft_strerror(data, 1, TOO_MANY_ARGS);
		return ;
	}
	old_pwd = grep_var_as_string((*data)->envp, "PWD=");
	if (chdir(path) == -1)
	{
		free(path);
		ft_strerror(data, 1, NO_SUCH_FILE_DIR);
		return ;
	}
	free(path);
	change_env(data, "OLDPWD=", old_pwd);
	pwd = getcwd(pwd, 255);
	if (pwd)
		change_env(data, "PWD=", pwd);
}
