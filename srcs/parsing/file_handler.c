/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:42:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/02 13:47:11 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_outfiles(t_token *tokens, t_data **data, t_TYPE type)
{
	int	o_flags;

	tokens->arg = delete_quotes(tokens->arg);
	safe_close((*data)->out);
	if (type == OUTFILE)
		o_flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		o_flags = O_WRONLY | O_APPEND | O_CREAT;
	(*data)->out = open(tokens->arg, o_flags, 0777);
}

static int	set_outfile(t_data **data, t_token *tokens)
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
			return (0);
		}
		tokens = tokens->next;
	}
	(*data)->out_tmp = (*data)->out;
	return (1);
}

static void	handle_infiles(t_token *tokens, t_data **data, t_TYPE type)
{
	tokens->arg = delete_quotes(tokens->arg);
	safe_close((*data)->in);
	if (type == HEREDOC)
		ft_heredoc(tokens->arg, data);
	else
		(*data)->in = open(tokens->arg, O_RDONLY);
}

static int	set_infile(t_data **data, t_token *tokens)
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

int	set_file_descriptors(t_data **data, t_token *tokens)
{
	if (!set_infile(data, tokens))
	{
		ft_putendl_fd(INVALID_INFILE, 2);
		return (0);
	}
	else if (!set_outfile(data, tokens))
	{
		ft_putendl_fd(INVALID_OUTFILE, 2);
		return (0);
	}
	return (1);
}
