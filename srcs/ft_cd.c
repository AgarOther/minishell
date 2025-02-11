/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:45:07 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/11 15:59:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_pwd(t_data *data, char *pwd)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 4;
	while (ft_strncmp(data->envp[i], "PWD=", 4) != 0)
		i++;
	while (pwd[j])
	{
		data->envp[i][k] = pwd[j];
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
	tmp = ft_strjoin(pwd, args[1]);
	if (access(tmp, F_OK))
	{	
		pwd = ft_strjoin(pwd, "/");
		pwd = ft_strjoin_free(pwd, args[1]);
		change_pwd( data, pwd);
		free(pwd);
	}
	free(tmp);
		
}

void	change_old_pwd(t_data *data, char *pwd)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 7;
	while (ft_strncmp(data->envp[i], "OLDPWD=", 7) != 0)
		i++;
	while (pwd[j])
	{
		data->envp[i][k] = pwd[j];
		j++;
		k++;
	}
}
void	ft_cd(t_data *data)
{
	char	**tab;
	char	*pwd;
	int		len;
	int		len2;

	tab = grep_var(data->envp, "PWD=");
	pwd = tab[0];
	change_old_pwd(data, pwd);
	if (ft_strlencmp(data->input, "cd ..", 0) == 0)
	{	
		len2 = ft_strlen(pwd) - 1;
		while (len2 >= 0 && pwd[len2] != '/')
			len2--;
		len = ft_strlen(pwd);
		pwd = ft_substr(pwd, 0, len2);
		if (!pwd || !pwd[0])
			change_pwd(data, "/");
		else
			change_pwd(data, pwd);
	}
	else
		cd_goto(data, pwd);
}
