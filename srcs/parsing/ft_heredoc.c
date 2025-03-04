/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:36:37 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/04 16:51:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(char *str, int tmp_fd, t_data **data, char *path)
{
	free(str);
	close(tmp_fd);
	(*data)->in = open(path, O_RDONLY);
	free(path);
}

void	ft_heredoc(char *limiter, t_data **data)
{
	static int	count = 0;
	char		*str;
	char		*filepath;
	int			tmp_fd;

	str = NULL;
	filepath = get_tmp_filepath(count++);
	tmp_fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
	{
		free(filepath);
		exit(-1);
	}
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, limiter) == 0)
			break ;
		write(tmp_fd, str, ft_strlen(str));
		free(str);
	}
	handle_heredoc(str, tmp_fd, data, filepath);
}
