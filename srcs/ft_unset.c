/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:49:28 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/13 16:45:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_list_remove_if(t_data *data, char *var, t_list *prev, t_list *cur)
{
	t_list	*head;

	head = cur;
	while (cur)
	{
		if (!ft_strncmp(var, cur->str, ft_strcharindex(cur->str, '=')))
		{
			if (prev == NULL)
				head = cur->next;
			else
				prev->next = cur->next;
			free(cur->str);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	free(var);
	update_env(head, data);
	ft_lstclear(&head);
}

void	ft_unset(t_data *data, char *var)
{
	t_list		*previous;
	t_list		*current;

	if (!var)
		return ;
	else if (!ft_stralnum(var))
	{
		ft_putendl_fd("Error: Invalid parameter name.", 2);
		return ;
	}
	var = ft_strjoin(var, "=");
	previous = NULL;
	current = get_env_as_lst(data);
	ft_list_remove_if(data, var, previous, current);
}
