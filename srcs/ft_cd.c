/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:45:07 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/18 12:44:02 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_env(t_data *data, char *env, char *new)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = ft_strlen(env);
	while (ft_strncmp(data->envp[i], env, k) != 0)
		i++;
	while (new[j])
	{
		data->envp[i][k] = new[j];
		j++;
		k++;
	}
	data->envp[i][k] = 0;
}

void	cd_goto(t_data *data, char *pwd)
{
	char	**args;
	char	*tmp;

	args = ft_split(data->input, ' ');
	if (pwd[ft_strlen(pwd) - 1] != '/')
		pwd = ft_strjoin_free(pwd, "/");
	tmp = ft_strjoin(pwd, args[1]);
	ft_printf("%s\n", tmp);
	if (!access(tmp, F_OK))
	{
		pwd = ft_strjoin(pwd, "/");
		pwd = ft_strjoin_free(pwd, args[1]);
		chdir(grep_var(data->envp, "PWD=")[0]);
		change_env(data, "PWD=", pwd);
		free(pwd);
	}
	else
		ft_putendl_fd("Error: Directory doesn't exist.", 2);
	free(tmp);
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
		chdir(grep_var(data->envp, "PWD=")[0]);
	}
	else
		cd_goto(data, pwd);
}
