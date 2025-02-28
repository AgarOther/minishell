/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stratoiable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:03:38 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/28 11:55:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stratoiable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}
