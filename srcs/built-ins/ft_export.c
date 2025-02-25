/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 15:11:14 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstprint_export(t_list *lst)
{
	t_list	*tmp;
	char	*to_sub;

	tmp = lst;
	while (tmp)
	{
		to_sub = ft_substr(&tmp->str[ft_strcharindex(tmp->str, '=')], 2,
				ft_strlen(&tmp->str[ft_strcharindex(tmp->str, '=')]));
		tmp->sptstr = ft_split(tmp->str, '=');
		if (!tmp->sptstr[1])
		{
			if (ft_strchr(tmp->str, '='))
			{
				tmp->str = ft_strjoin_free(tmp->str, "=");
				tmp->str = ft_strjoin_free(tmp->str, "\"");
				tmp->str = ft_strjoin_free(tmp->str, "\"");
			}
			free(tmp->str);
			tmp->str = ft_strjoin("declare -x ", tmp->sptstr[0]);
			ft_putendl_fd(tmp->str, 1);
			ft_tabfree(tmp->sptstr, ft_tablen(tmp->sptstr));
			free(to_sub);
			tmp = tmp->next;
			continue ;
		}
		free(tmp->str);
		tmp->str = ft_strjoin("declare -x ", tmp->sptstr[0]);
		to_sub = addquotes(to_sub);
		tmp->str = ft_strjoin_free(tmp->str, "=");
		tmp->str = ft_strjoin_free(tmp->str, to_sub);
		tmp->str = ft_strjoin_free(tmp->str, "\"");
		ft_putendl_fd(tmp->str, 1);
		ft_tabfree(tmp->sptstr, ft_tablen(tmp->sptstr));
		free(to_sub);
		tmp = tmp->next;
	}
}

static t_list	*get_highest(t_list *envp)
{
	t_list	*tmp;
	t_list	*highest;

	tmp = envp;
	highest = tmp;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, highest->str,
				ft_strcharindex(tmp->str, '=')) < 0)
			highest = tmp;
		tmp = tmp->next;
	}
	return (highest);
}

static void	print_sorted(t_data *data)
{
	t_list	*envp;
	t_list	*sorted;
	t_list	*highest;
	char	*to_add;

	envp = get_env_as_lst(data);
	if (!envp)
		return ;
	sorted = NULL;
	while (envp)
	{
		highest = get_highest(envp);
		to_add = ft_strdup(highest->str);
		if (!sorted)
			sorted = ft_lstnew(to_add);
		else
			ft_lstadd_back(&sorted, ft_lstnew(to_add));
		envp = ft_list_remove_if(highest->str, envp, 0);
	}
	ft_lstprint_export(sorted);
	ft_lstclear(&sorted);
	ft_lstclear(&envp);
}

static void	modify_var(t_list **envp, char *to_grep, char *arg)
{
	t_list	*tmp;
	int		len;

	tmp = *envp;
	len = ft_strlen(to_grep);
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, to_grep, len))
		{
			free(tmp->str);
			tmp->str = ft_strdup(arg);
			break ;
		}
		tmp = tmp->next;
	}
	free(arg);
}

void	ft_export(t_data *data, char *arg)
{
	t_list	*envp;
	char	**var;
	char	*to_grep;
	int		sign_index;

	if (!arg)
		return (print_sorted(data));
	else if (ft_strstartswith(arg, "="))
		return (ft_putendl_fd("Error: Bad assignment.", 2));
	envp = get_env_as_lst(data);
	sign_index = ft_strcharindex(arg, '=');
	to_grep = ft_substr(arg, 0, sign_index);
	var = grep_var(data->envp, to_grep);
	if (!var)
		ft_lstadd_back(&envp, ft_lstnew(arg));
	else
		modify_var(&envp, to_grep, arg);
	update_env(envp, data);
	free(to_grep);
	if (var)
		ft_tabfree(var, ft_tablen(var));
	ft_lstclear(&envp);
}
