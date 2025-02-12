/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:37:13 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/12 16:01:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_tokenclear(t_token **token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->arg);
		free(tmp);
	}
	token = NULL;
}
