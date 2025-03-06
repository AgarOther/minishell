/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 18:51:47 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_arg(char **envarg, char **args, t_list *tmp)
{
	char	*arg;

	arg = ft_strjoin(envarg[0], "=");
	arg = ft_strjoin_free(arg, envarg[1]);
	arg = ft_strjoin_free(arg, args[1]);
	free(tmp->str);
	tmp->str = ft_strdup(arg);
	ft_tabfree(args, ft_tablen(args));
	ft_tabfree(envarg, ft_tablen(envarg));
	return (arg);
}

static int	modify_var(t_list *envp, char *arg, char *tmparg)
{
	t_list	*tmp;
	int		i;
	char	**args;
	char	**envarg;

	tmp = envp;
	i = 0;
	while (arg[i] != '=')
		i++;
	while (ft_strncmp(arg, tmp->str, ft_strcharindex(arg, '=') + 1))
		tmp = tmp->next;
	if (ft_strcontains(tmparg, "+="))
	{
		args = ft_splitfirst(arg, '=');
		envarg = ft_splitfirst(tmp->str, '=');
		arg = fill_arg(envarg, args, tmp);
	}
	else
	{
		free(tmp->str);
		tmp->str = ft_strdup(arg);
	}
	return (1);
}

static int	already_exists(t_list *envp, char *arg, char *tmparg, t_data **data)
{
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(arg, tmp->str, ft_strcharindex(arg, '=') + 1))
		{
			if (!ft_strchr(arg, '='))
				return (1);
			else
			{
				modify_var(envp, arg, tmparg);
				update_env(envp, data);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_export(t_data **data, char *arg, t_list *envp, char *tmparg)
{		
	if (!arg)
		return (print_sorted(*data));
	else if (ft_tokencount((*data)->tokens, PIPE) > 0)
		return (free(arg));
	else if (ft_strstartswith(arg, "=") || !is_exportable(arg))
	{
		free(arg);
		return (ft_strerror(data, 1, BAD_ASSIGNMENT));
	}
	envp = get_env_as_lst(*data);
	arg = delete_quotes(arg, 1);
	tmparg = ft_strdup(arg);
	if (ft_strcontains(arg, "+="))
		arg = rm_first_occur(arg, '+');
	if (already_exists(envp, arg, tmparg, data))
		return (free(arg));
	ft_lstadd_back(&envp, ft_lstnew(arg));
	update_env(envp, data);
	ft_lstclear(&envp);
}
