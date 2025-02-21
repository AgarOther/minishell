/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokensize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:40:25 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/21 13:41:00 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokensize(t_token *token)
{
	int	count;

	if (!token)
		return (0);
	count = 1;
	while (token->next)
	{
		token = token->next;
		count++;
	}
	return (count);
}
