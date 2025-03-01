/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:01:41 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/01 22:05:48 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *path)
{
	DIR	*dir;
	int	val;

	dir = opendir(path);
	if (!dir)
		val = 0;
	else
		val = 1;
	if (val)
		closedir(dir);
	return (val);
}
