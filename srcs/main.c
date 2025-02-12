/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 16:40:11 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	t_token		*tokens;

	data = setup_data(envp);
	if (!data)
		return (1);
	while (1 && ac != ((int)**av) + ac) // tkt
	{
		data->input = readline(PROMPT);
		if (!data->input)
			continue ;
		else if (!data->input[0])
			continue ;
		add_history(data->input);
		data = fill_data(data, 0);
		if (!has_invalid_quotes(data->input))
		{
			ft_putendl_fd("Error: Invalid quotes.", 2);
			data->cmds = NULL;
			free_data(data, 0);
			continue ;
		}
		tokens = get_tokens(data);
		if (tokens)
		{
			get_parsed_input(&data, tokens);
			print_tokens(tokens);
			split_cmds(data);
			ft_tokenclear(&tokens);
		}
		free_data(data, 0);
	}
}
