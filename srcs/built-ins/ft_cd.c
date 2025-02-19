/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:45:07 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/19 17:06:11 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(t_data *data, char *path)
{
	char	**var;
	int		retval;

	var = grep_var(data->envp, path);
	if (!var)
		return (-1);
	retval = chdir(var[0]);
	if (retval == -1)
		ft_putendl_fd("ah oui ok d'accord", 2);
	ft_tabfree(var, ft_tablen(var));
	return (retval);
}

void	change_env(t_data *data, char *env, char *new)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	j = 0;
	k = ft_strlen(env);
	while (ft_strncmp(data->envp[i], env, k) != 0)
		i++;
	tmp = ft_strdup(data->envp[i]);
	free(data->envp[i]);
	data->envp[i] = ft_calloc(k + ft_strlen(new) + 1, 1);
	ft_strlcpy(data->envp[i], tmp, ft_strlen(env) + 1);
	free(tmp);
	while (new[j])
	{
		data->envp[i][k] = new[j];
		j++;
		k++;
	}
}

static void	free_vars(char **args, char *tmp, char *pwd)
{
	ft_tabfree(args, ft_tablen(args));
	free(tmp);
	free(pwd);
}

void	cd_goto(t_data *data, char *pwd)
{
	char	**args;
	char	*tmp;

	args = ft_split(data->input, ' ');
	pwd = ft_strjoin_free(ft_strdup(pwd), "/");
	tmp = ft_strjoin(pwd, args[1]);
	if (!access(tmp, F_OK))
	{
		pwd = ft_strjoin_free(pwd, args[1]);
		if (pwd[ft_strlen(pwd) - 1] == '/')
			pwd = ft_strcrop(pwd, 1);
		if (chdir(tmp))
		{
			ft_putendl_fd("ah oui ok d'accord", 2);
			free_vars(args, tmp, pwd);
			return ;
		}
		change_env(data, "PWD=", pwd);
	}
	else
		ft_putendl_fd("Error: Directory doesn't exist.", 2);
	free_vars(args, tmp, pwd);
}

void	ft_cd(t_data *data)
{
	char	**tab;
	char	*pwd;
	int		len;
	char	*oldpwd;

	tab = grep_var(data->envp, "PWD=");
	pwd = tab[0];
	oldpwd = pwd;
	change_env(data, "OLDPWD=", oldpwd);
	if (ft_strlencmp(data->input, "cd ..", 0) == 0)
	{
		len = ft_strlen(pwd) - 1;
		while (len >= 0 && pwd[len] != '/')
			len--;
		pwd = ft_substr(pwd, 0, len);
		if (!pwd || !pwd[0])
			change_env(data, "PWD=", "/");
		else
			change_env(data, "PWD=", pwd);
		ft_chdir(data, "PWD=");
		free(pwd);
	}
	else
		cd_goto(data, pwd);
	ft_tabfree(tab, ft_tablen(tab));
}
