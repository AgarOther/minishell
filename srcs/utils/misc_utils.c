/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:01:41 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 00:52:34 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tmp_filepath(int cmd_count)
{
	char	*filepath;
	char	*count;

	count = ft_itoa(cmd_count);
	if (!count)
		return (NULL);
	filepath = ft_strjoin(TMP_FILEPATH, count);
	free(count);
	return (filepath);
}

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
