/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:42:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/01 18:36:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_outfiles(t_token *tokens, t_data **data, t_TYPE type)
{
	int	o_flags;

	safe_close((*data)->out);
	if (type == OUTFILE)
		o_flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		o_flags = O_WRONLY | O_APPEND | O_CREAT;
	(*data)->out = open(tokens->arg, o_flags, 0777);
}

int	set_outfile(t_data **data, t_token *tokens)
{
	if (!ft_tokencount(tokens, OUTFILE) && !ft_tokencount(tokens, APPENDFILE))
		return (1);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == OUTFILE || tokens->type == APPENDFILE)
			handle_outfiles(tokens, data, tokens->type);
		if ((*data)->out == -1)
		{
			(*data)->exit_code = 1;
			(*data)->outfile_err = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	(*data)->out_tmp = (*data)->out;
	return (1);
}

static void	handle_infiles(t_token *tokens, t_data **data, t_TYPE type)
{
	safe_close((*data)->in);
	if (type == HEREDOC)
		ft_heredoc(tokens->arg, data);
	else
		(*data)->in = open(tokens->arg, O_RDONLY);
}

int	set_infile(t_data **data, t_token *tokens)
{
	if (!ft_tokencount(tokens, INFILE) && !ft_tokencount(tokens, HEREDOC))
		return (1);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == INFILE || tokens->type == HEREDOC)
			handle_infiles(tokens, data, tokens->type);
		if ((*data)->in == -1)
		{
			(*data)->exit_code = 1;
			return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
