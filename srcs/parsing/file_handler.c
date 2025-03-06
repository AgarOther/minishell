/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:42:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/06 20:37:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_outfile(t_data **data, t_token *tokens, t_type type)
{
	int	o_flags;

	tokens->arg = delete_quotes(tokens->arg, 1, -1);
	safe_close((*data)->out);
	if (type == OUTFILE)
		o_flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		o_flags = O_WRONLY | O_APPEND | O_CREAT;
	(*data)->out = open(tokens->arg, o_flags, 0777);
	return ((*data)->out);
}

static int	handle_infile(t_data **data, t_token *tokens, t_type type)
{
	tokens->arg = delete_quotes(tokens->arg, 1, -1);
	safe_close((*data)->in);
	if (type == HEREDOC)
		ft_heredoc(tokens->arg, data);
	else
		(*data)->in = open(tokens->arg, O_RDONLY);
	return ((*data)->in);
}

int	set_file_descriptors(t_data **data, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == INFILE || tokens->type == HEREDOC)
		{
			if (handle_infile(data, tokens, tokens->type) == -1)
			{
				ft_strerror(data, 1, INVALID_INFILE);
				return (0);
			}
		}
		else if (tokens->type == OUTFILE || tokens->type == APPENDFILE)
		{
			if (handle_outfile(data, tokens, tokens->type) == -1)
			{
				ft_strerror(data, 1, INVALID_OUTFILE);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
