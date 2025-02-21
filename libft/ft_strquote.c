/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:29:02 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/21 15:37:02 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strquote(char *str, char quote, int free_str)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = ft_calloc(len + 3, 1);
	if (!new)
		return (NULL);
	new[0] = quote;
	ft_strlcat(&new[1], str, ft_strlen(&new[1]) + len + 1);
	new[len + 1] = quote;
	if (free_str)
		free(str);
	return (new);
}
