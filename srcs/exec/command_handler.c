/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:20:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/01 19:01:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_commands(t_data *data)
{
	data->input = expand_command(data, data->input, -1, -1);
	get_tokens(&data);
	if (data->tokens && has_invalid_syntax(data))
		ft_putendl_fd(INVALID_SYNTAX, 2);
	else if (data->tokens)
	{
		data->nb_cmds = ft_tokencount(data->tokens, COMMAND);
		data->cmd_count = 0;
		data->outfile_err = 0;
		data->in = 0;
		data->out = 1;
		data->out_tmp = 1;
		if (data->nb_cmds)
			data = fill_data(data);
		process_tokens(&data);
	}
}
