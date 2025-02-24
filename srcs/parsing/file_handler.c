/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:42:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 13:17:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_appendfile(t_data **data)
{
	t_token	*tokens;

	tokens = (*data)->tokens;
	if (ft_tokencount(tokens, APPENDFILE) == 0)
		return (1);
	while (tokens)
	{
		if (tokens->type == APPENDFILE)
		{
			if ((*data)->out > 1)
				close((*data)->out);
			(*data)->out = open(tokens->arg,
					O_WRONLY | O_APPEND | O_CREAT, 0777);
		}
		if ((*data)->out == -1)
		{
			(*data)->exit_code = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	set_outfile(t_data **data)
{
	t_token	*tokens;

	tokens = (*data)->tokens;
	if (ft_tokencount(tokens, OUTFILE) == 0)
		return (1);
	while (tokens)
	{
		if (tokens->type == OUTFILE)
		{
			if ((*data)->out > 1)
				close((*data)->out);
			(*data)->out = open(tokens->arg,
					O_WRONLY | O_TRUNC | O_CREAT, 0777);
		}
		if ((*data)->out == -1)
		{
			(*data)->exit_code = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

static int	set_infile(t_data **data)
{
	t_token	*tokens;

	tokens = (*data)->tokens;
	if (ft_tokencount(tokens, INFILE) == 0)
		return (1);
	while (tokens)
	{
		if (tokens->type == INFILE)
		{
			if ((*data)->in > 0)
				close((*data)->in);
			(*data)->in = open(tokens->arg, O_RDONLY);
		}
		if ((*data)->in == -1)
		{
			(*data)->exit_code = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

int	set_file_descriptors(t_data **data)
{
	(*data)->in = 0;
	(*data)->out = 1;
	if (!set_infile(data))
	{
		ft_putendl_fd("Error: Invalid infile.", 2);
		return (0);
	}
	else if (!set_outfile(data))
	{
		ft_putendl_fd("Error: Invalid outfile.", 2);
		return (0);
	}
	else if (!set_appendfile(data))
	{
		ft_putendl_fd("Error: Invalid append outfile.", 2);
		return (0);
	}
	return (1);
}
