/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 13:08:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = setup_data(envp);
	if (!data)
		return (1);
	while (1 && ac != ((int)**av) + ac)
	{
		intercept_signals();
		data->input = readline(PROMPT);
		if (g_signal)
		{
			if (g_signal == SIGINT)
				data->exit_code = 130;
			g_signal = 0;
		}
		if (!data->input)
			break ;
		else if (!data->input[0])
			continue ;
		add_history(data->input);
		if (has_invalid_quotes(data->input))
		{
			ft_putendl_fd("Error: Invalid quotes.", 2);
			free_data(data, 0);
			data->exit_code = 2;
			continue ;
		}
		handle_commands(data);
		free_data(data, 0);
	}
	return (free_data(data, 1));
}
