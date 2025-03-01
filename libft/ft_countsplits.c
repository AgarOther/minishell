/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countsplits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:52:15 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/28 13:42:29 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countsplits(const char *str, char c)
{
	int	i;
	int	strs;
	int	is_spaced;

	i = 0;
	strs = 0;
	is_spaced = 1;
	while (str[i])
	{
		if (is_spaced && str[i] != c)
		{
			is_spaced = 0;
			strs++;
		}
		else if (!is_spaced && str[i] == c)
			is_spaced = 1;
		i++;
	}
	return (strs);
}
