/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/06 17:13:39 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		i;
	int		nb_cmds;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	data->in = 0;
	data->out = 0;
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
		nb_cmds = ft_tablen(data->cmds);
		data->pids = ft_calloc(sizeof(pid_t), nb_cmds + 1);
		if (nb_cmds > 1)
		{
			data->pipes = malloc(sizeof(int *) * (nb_cmds - 1));
			i = 0;
			while (i < nb_cmds - 1)
			{
				data->pipes[i] = malloc(sizeof(int) * 2);
				pipe(data->pipes[i]);
				i++;
			}
		}
		if (!data->pids)
		{
			// Free all
			return (4);
		}
		exec_cmds(data);
		free(input);
	}
}
