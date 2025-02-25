/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:29:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 14:43:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strquote(char *str, char quote, char index1, char index2)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 3, 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i - 1] == index1 || str[i + 1] == index2)
		{
			new[j] = quote;
			j++;
		}
		new[j++] = str[i++];
	}
	new[j] = 0;
	return (new);
}
