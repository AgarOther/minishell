/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 23:20:49 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 23:48:09 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_commands(t_data *data)
{
	data->input = expand_command(data, data->input, -1, -1);
	get_tokens(&data);
	if (data->tokens && has_invalid_syntax(data))
	{
		print_tokens(data->tokens);
		ft_putendl_fd("Error: Invalid syntax.", 2);
	}
	else if (data->tokens)
	{
		data->nb_cmds = ft_tokencount(data->tokens, COMMAND);
		//print_tokens(data->tokens);
		if (data->nb_cmds)
		{
			data = fill_data(data, 0);
			process_tokens(&data);
		}
	}
}
