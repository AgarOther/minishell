/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:28:59 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/10 15:31:37 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (*token)
	{
		tmp = *token;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*token = new;
}
