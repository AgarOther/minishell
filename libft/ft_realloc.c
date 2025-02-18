/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:05:33 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/18 14:12:38 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old, int old_size, int new_size)
{
	void	*new;

	if (!old || old_size <= 0 || new_size <= 0)
		return (NULL);
	new = ft_calloc(new_size, 1);
	if (!new)
		return (NULL);
	if (old_size < new_size)
		ft_memmove(new, old, old_size);
	else
		ft_memmove(new, old, new_size);
	free(old);
	return (new);
}
