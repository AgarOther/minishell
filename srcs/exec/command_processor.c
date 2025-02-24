/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:15:29 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/24 23:22:46 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*construct_command(t_token *tokens)
{
	char	*command;

	command = ft_strdup(tokens->arg);
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->type == APPENDFILE
				|| tokens->type == OUTFILE)
			return (command);
		else
			command = ft_strjoin_free(command, " ");
		command = ft_strjoin_free(command, tokens->arg);
		tokens = tokens->next;
	}
	return (command);
}

void	process_tokens(t_data *data)
{
	char	*cmd;
	t_token	*tokens;

	if (!set_file_descriptors(&data))
		return ;
	tokens = data->tokens;
	while (tokens)
	{
		if (tokens->type == COMMAND)
		{
			cmd = construct_command(tokens);
			ft_printf("Reconstructed command is: %s$\n", cmd);
			execute_command(data, cmd);
			free(cmd);
			while (tokens && tokens->type != PIPE && tokens->type != APPENDFILE
				&& tokens->type != OUTFILE)
				tokens = tokens->next;
		}
		if (tokens)
			tokens = tokens->next;
	}
}
