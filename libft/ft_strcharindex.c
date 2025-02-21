/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharindex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:49:42 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/20 15:16:47 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcharindex(char *str, char c)
{
	int	i;

	i = 0;
	if (!ft_strchr(str, c))
		return (ft_strlen(str));
	while (str[i] && str[i] != c)
		i++;
	return (i - 1);
}
