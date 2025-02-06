/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/06 16:49:25 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (1);
	(void) ac;
	(void) av;
	data->envp = ft_tabdup(envp, ft_tablen(envp));
	if (!data->envp)
	{
		free(data);
		return (2);
	}
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		add_history(input);
		data->cmds = ft_split(input, '|');
		if (!data->cmds)
		{
			// Free all
			return (3);
		}
		data->pids = ft_calloc(sizeof(pid_t), ft_tablen(data->cmds) + 1);
		if (!data->pids)
		{
			// Free all
			return (4);
		}
		exec_cmds(data);
		free(input);
	}
}
