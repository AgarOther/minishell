/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/13 15:04:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler()
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals()
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = setup_data(envp);
	if (!data)
		return (1);
	handle_signals();
	while (1 && ac != ((int)**av) + ac) // tkt
	{
		data->input = readline(PROMPT);
		if (!data->input || !data->input[0])
			break ;
		add_history(data->input);
		if (!has_invalid_quotes(data->input))
		{
			ft_putendl_fd("Error: Invalid quotes.", 2);
			data->cmds = NULL;
			free_data(data, 0);
			continue ;
		}
		get_tokens(&data);
		if (data->tokens)
		{
			get_parsed_input(&data, data->tokens);
			data = fill_data(data, 0);
			print_tokens(data->tokens);
			split_cmds(data);
		}
		free_data(data, 0);
	}
	free_data(data, 1);
}
