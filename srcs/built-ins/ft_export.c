/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 15:07:10 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exportable(char *arg)
{
	int	i;

	if (!isalpha(arg[0]))
	{
		if (arg[0] != '\"' && arg[0] != '\'' && arg[0] != '_' && arg[0] != '`')
			return (0);
	}
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if ((arg[i] == '+' && arg[i] == '=') || arg[i] == '-' || arg[i] == 92 || arg[i] == '/' || arg[i] == '*'
			|| arg[i] == ':' || arg[i] == ';' || arg[i] == '{'|| arg[0] == '+'
			|| arg[i] == '}' || arg[i] == '(' || arg[i] == ')' || arg[i] == '&'
			|| arg[i] == '^' || arg[i] == '%' || arg[i] == '$' || arg[i] == '#'
			|| arg[i] == '@' || arg[i] == '!' || arg[i] == '<' || arg[i] == '>'
			|| arg[i] == '?' || arg[i] == ',' || arg[i] == '.' || arg[i] == '~'
			|| arg[i] == '`')
			return (0);
		i++;
	}
	return (1);
}

void	ft_lstprint_export(t_list *lst)
{
	t_list	*tmp;
	char **arg;
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
			arg[1] = delete_quotes(arg[1], 1);
			ft_printf("declare -x %s=\"%s\"\n", arg[0], arg[1]);
			ft_tabfree(arg, ft_tablen(arg));
		}
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

static int	modify_var(t_list *envp, char *arg)
{
	t_list	*tmp;
	int 	i;

	tmp = envp;
	i = 0;
	while (arg[i] != '=')
		i++;
	while (ft_strncmp(arg, tmp->str, ft_strcharindex(arg, '=')))	
		tmp = tmp->next;
	free(tmp->str);
	tmp->str = ft_strdup(arg);
	ft_printf("env : %s\n", tmp->str);
	ft_printf("arg : %s\n", arg);
	return (1);
}
	
static int	already_exists(t_list *envp, char *arg)
{
	t_list	*tmp;
		
	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp(arg, tmp->str, ft_strcharindex(arg, '=') + 1))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*rm_first_occur(char *arg, char c)
{
	int		i;
	int 	j;
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
	newarg[i] = 0;
	ft_printf("debug newarg : %s\n", newarg);
	ft_printf("debug arg : %s\n", arg);
	return (newarg);
}

void	ft_export(t_data **data, char *arg)
{
	t_list	*envp;
					
	if (!arg)
		return (print_sorted(*data));
	else if (ft_strstartswith(arg, "=") || !is_exportable(arg))
		return (ft_strerror(data, 1, BAD_ASSIGNMENT));
	envp = get_env_as_lst(*data);
	arg = delete_quotes(arg, 1);
	if (already_exists(envp, arg))
	{
		if (!ft_strchr(arg, '='))
			return ;
		else
		{
			modify_var(envp, arg);
			update_env(envp, *data);
			return ;
		}
	}
	if (ft_strcontains(arg, "+="))
		arg = rm_first_occur(arg, '+');
	t_list *new = ft_lstnew(arg);
	ft_lstadd_back(&envp, new);
	update_env(envp, *data);
	ft_lstclear(&envp);
}
				