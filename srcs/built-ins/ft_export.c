/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/19 17:06:04 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		to_add = ft_strjoin("declare -x ", highest->str);
		if (!sorted)
			sorted = ft_lstnew(to_add);
		else
			ft_lstadd_back(&sorted, ft_lstnew(to_add));
		envp = ft_list_remove_if(highest->str, envp, 0);
	}
	ft_lstprint(sorted, 1);
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
	else if (!ft_strchr(arg, '='))
		return ;
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
