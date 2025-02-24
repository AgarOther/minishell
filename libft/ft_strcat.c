/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:46:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 22:48:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	if (!src)
		return (dst);
	i = 0;
	j = ft_strlen(dst);
	while (src[i])
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = 0;
	return (dst);
}
