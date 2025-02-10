/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/10 17:38:43 by scraeyme         ###   ########.fr       */
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
			break ;
		else if (!data->input[0])
			continue ;
		add_history(data->input);
		//data = fill_data(data, 0);
		if (!cmd_valid(data->input))
		{
			ft_putendl_fd("Error: Invalid quotes.", 2);
			free_data(data, 0);
			continue ;
		}
		if (!ft_strncmp(data->input, "pwd", 3))
			ft_pwd(data);
		tokens = get_tokens(data);
		print_tokens(tokens);
		ft_tokenclear(&tokens);
		free_data(data, 0);
	}
}
