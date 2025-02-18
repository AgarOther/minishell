/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/18 12:42:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (!split_cmds(data))
				ft_putendl_fd("Error: Invalid input.", 2);
		}
		free_data(data, 0);
	}
	free_data(data, 1);
}
