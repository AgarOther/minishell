/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:34:54 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/18 12:42:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcrop(char *src, int to_crop)
{
	char	*str;
	int		src_len;
	int		i;

	src_len = ft_strlen(src);
	if (to_crop <= 0 || src_len - to_crop <= 0)
		return (NULL);
	str = ft_calloc(src_len - to_crop + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] && i < src_len - to_crop)
	{
		str[i] = src[i];
		i++;
	}
	free(src);
	return (str);
}
