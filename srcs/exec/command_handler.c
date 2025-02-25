/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:20:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/25 15:13:14 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_file_descriptors(t_data **data)
{
	(*data)->in = 0;
	(*data)->out = 1;
	(*data)->out_tmp = 1;
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
	return (1);
}

void	handle_commands(t_data *data)
{
	data->input = expand_command(data, data->input, -1, -1);
	get_tokens(&data);
	if (data->tokens && has_invalid_syntax(data))
		ft_putendl_fd("Error: Invalid syntax.", 2);
	else if (data->tokens)
	{
		data->nb_cmds = ft_tokencount(data->tokens, COMMAND);
		data->cmd_count = 0;
		if (data->nb_cmds)
			data = fill_data(data);
		process_tokens(&data);
	}
}
