/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:38:10 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/09 02:33:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_old_pwd(t_data **data, char *env)
{
	t_list	*envp;
	char	*oldpwd;
	char	*tmp;

	if (ft_strcmp(env, "PWD="))
		return ;
	tmp = grep_var_as_string((*data)->envp, "OLDPWD=");
	if (!tmp)
		return ;
	oldpwd = "OLDPWD=";
	envp = get_env_as_lst(*data);
	envp = ft_list_remove_if(oldpwd, envp, 0);
	update_env(envp, data);
	ft_lstclear(&envp);
}

static void	change_env(t_data **data, char *env, char *new)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = ft_strlen(env);
	while ((*data)->envp[i] && ft_strncmp((*data)->envp[i], env, k) != 0)
		i++;
	if (!(*data)->envp[i])
	{
		delete_old_pwd(data, env);
		free(new);
		return ;
	}
	tmp = ft_strdup((*data)->envp[i]);
	free((*data)->envp[i]);
	(*data)->envp[i] = ft_calloc(k + ft_strlen(new) + 1, 1);
	ft_strlcpy((*data)->envp[i], tmp, ft_strlen(env) + 1);
	free(tmp);
	while (new[j])
		(*data)->envp[i][k++] = new[j++];
	free(new);
	(*data)->exit_code = 0;
}

static void	handle_error(t_data **data, char *path, char *old_pwd)
{
	if (!access(path, F_OK) && !is_directory(path))
		ft_strerror(data, 1, NOT_A_DIR);
	else
		ft_strerror(data, 1, NO_SUCH_FILE_DIR);
	if (old_pwd)
		free(old_pwd);
}

void	ft_cd(t_data **data, char **cmd, char *pwd)
{
	int		len;
	char	*old_pwd;
	char	*path;

	len = ft_tablen(cmd);
	if (len < 2 || ft_tokencount((*data)->tokens, PIPE))
		return ;
	else if (len > 2)
	{
		ft_strerror(data, 1, TOO_MANY_ARGS);
		return ;
	}
	path = delete_quotes(cmd[1], 0, -1);
	old_pwd = ft_strdup(grep_var_as_string((*data)->envp, "PWD="));
	if (chdir(path) == -1)
	{
		handle_error(data, path, old_pwd);
		free(path);
		return ;
	}
	free(path);
	if (old_pwd)
		change_env(data, "OLDPWD=", old_pwd);
	pwd = getcwd(pwd, 0);
	change_env(data, "PWD=", pwd);
}
