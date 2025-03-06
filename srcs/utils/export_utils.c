/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:37:10 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 20:55:52 by scraeyme         ###   ########.fr       */
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

void	print_sorted(t_data *data)
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

int	is_exportable(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]))
	{
		if (arg[0] != '\"' && arg[0] != '\'' && arg[0] != '_' && arg[0] != '`')
			return (0);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if ((!(arg[i] == '+' && arg[i + 1] == '=')
				&& is_blacklist(arg[i])))
			return (0);
		i++;
	}
	return (1);
}

void	ft_lstprint_export(t_list *lst)
{
	t_list	*tmp;
	char	**arg;

	tmp = lst;
	while (tmp)
	{
		if (tmp->str[ft_strlen(tmp->str) - 1] == '=')
			ft_printf("declare -x %s\"\"\n", tmp->str);
		else if (!ft_strchr(tmp->str, '='))
			ft_printf("declare -x %s\n", tmp->str);
		else if (tmp->str[0] != '_' || tmp->str[1] != '=')
		{
			arg = ft_splitfirst(tmp->str, '=');
			arg[1] = delete_quotes(arg[1], 1, -1);
			ft_printf("declare -x %s=\"%s\"\n", arg[0], arg[1]);
			ft_tabfree(arg, ft_tablen(arg));
		}
		tmp = tmp->next;
	}
}

char	*rm_first_occur(char *arg, char c)
{
	int		i;
	int		j;
	char	*newarg;

	j = 0;
	i = 0;
	newarg = ft_calloc(ft_strlen(arg), 1);
	while (arg[i])
	{
		if (arg[i] == c && arg[i + 1] == '=')
			i++;
		newarg[j] = arg[i];
		i++;
		j++;
	}
	newarg[j] = 0;
	free(arg);
	return (newarg);
}
