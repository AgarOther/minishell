/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:30:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/13 17:18:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_sorted(t_data *data)
{
	(void)data;
	ft_printf("NOOOOOOOOOOOOOOOOOOON\n");
}

void	ft_export(t_data *data, char *arg)
{
	t_list	*env;
	char	**var;
	char	*tmp;
	int		sign_pos;

	if (!arg)
		return (print_sorted(data)); // Sort oscour
	else if (!ft_strchr(arg, '='))
		return ;
	env = get_env_as_lst(data);
	sign_pos = ft_strcharindex(arg, '=') - 1;
	tmp = ft_substr(arg, 0, sign_pos);
	var = grep_var(data->envp, tmp);
	if (!var)
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(arg)));
	else
		ft_tabfree(var, ft_tablen(var));
	free(tmp);
	update_env(env, data);
	ft_lstclear(&env);
}
