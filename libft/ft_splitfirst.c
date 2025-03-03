/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitfirst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:07:24 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/03 13:36:23 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_splitfirst(char *str, char c)
{
	char    **tab;
	int        index;

	if (!str)
		return (NULL);
	else if (ft_strchr(str, c))
	{
		if (!str[ft_strcharindex(str, '=') + 2])
			return (ft_split(str, c));
		tab = ft_calloc(sizeof(char *), 3);
	}
	else
		return (ft_split(str, c));
	if (!tab)
		return (NULL);
	index = ft_strcharindex(str, '=');
	tab[0] = ft_substr(str, 0, index + 1);
	tab[1] = ft_substr(str, index + 2, ft_strlen(str) - index);
	return (tab);
}
