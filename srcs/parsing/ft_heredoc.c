/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:36:37 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 16:17:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc(char *str, int tmp_fd)
{
	if (str)
		free(str);
	else
		ft_putendl_fd(WARN_EOF, 2);
	close(tmp_fd);
}

void	list_to_file(t_list *lst, int tmp_fd)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		write(tmp_fd, tmp->str, ft_strlen(tmp->str));
		tmp = tmp->next;
	}
	if (lst)
		ft_lstclear(&lst);
}

char	*expand_heredoc(t_data *data, char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(get_alloc_size(data, str, -1, 0) + 1, 1);
	while (new && str[i])
	{
		if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1])
			&& str[i + 1] != '$')
		{
			j += get_expanded(data, &str[i], new);
			i += get_sepindex(&str[i + 1]);
		}
		else
			new[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (new);
}

void	execute_heredoc(int tmp_fd, char *limiter, t_data **data, int quoted)
{
	t_list	*lst;
	t_list	*new;
	char	*str;

	lst = NULL;
	str = NULL;
	intercept_signals();
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(str, limiter) == 0)
			break ;
		if (!quoted)
			str = expand_heredoc(*data, str);
		if (!str)
			break ;
		str = ft_strjoin_free(str, "\n");
		new = ft_lstnew(str);
		if (!lst)
			lst = new;
		else
			ft_lstadd_back(&lst, new);
	}
	list_to_file(lst, tmp_fd);
	handle_heredoc(str, tmp_fd);
}

void	ft_heredoc(char *limiter, t_data **data, int quoted)
{
	static int	count = 0;
	char		*path;
	int			tmp_fd;

	path = get_tmp_filepath(count++);
	tmp_fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
	{
		free(path);
		exit(-1);
	}
	execute_heredoc(tmp_fd, limiter, data, quoted);
	if (path)
	{
		(*data)->in = open(path, O_RDONLY);
		free(path);
	}
	prevent_signals();
}
