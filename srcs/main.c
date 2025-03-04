/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/04 23:26:24 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	change_signal_value(int value)
{
	g_signal = value;
}

static char	*readline_and_signal(t_data **data)
{
	char	*str;

	str = readline(PROMPT);
	if (g_signal)
	{
		(*data)->exit_code = g_signal;
		g_signal = 0;
	}
	return (str);
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
		data->input = readline_and_signal(&data);
		if (!data->input)
			break ;
		else if (!data->input[0] || ft_isfilled(data->input, ' ', NULL))
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
