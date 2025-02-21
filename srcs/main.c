/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/21 15:37:21 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	intercept_signals(void)
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
	intercept_signals();
	while (1 && ac != ((int)**av) + ac) // tkt
	{
		data->input = readline(PROMPT);
		if (!data->input)
			break ;
		else if (!data->input[0])
			continue ;
		add_history(data->input);
		if (has_invalid_quotes(data->input))
		{
			ft_putendl_fd("Error: Invalid quotes.", 2);
			data->cmds = NULL;
			free_data(data, 0);
			continue ;
		}
		data->input = expand_command(data, data->input, 0, 0);
		get_tokens(&data);
		if (data->tokens && has_invalid_syntax(data))
		{
			print_tokens(data->tokens);
			ft_putendl_fd("Error: Invalid syntax.", 2);
			data->cmds = NULL;
		}
		else if (data->tokens)
		{
			get_parsed_input(&data, data->tokens);
			print_tokens(data->tokens);
			if (data->nb_cmds)
			{
				data = fill_data(data, 0);
				if (!split_cmds(data))
					ft_putendl_fd("Error: Invalid command.", 2);
			}
		}
		free_data(data, 0);
	}
	free_data(data, 1);
}
