/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:06 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/06 14:55:07 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*tmp;
	t_data	data;

	(void) ac;
	(void) av;
	(void) envp;
	data.envp = ft_tabdup(envp, ft_tablen((const char **)envp));
	tmp = readline(PROMPT);
	add_history(tmp);
	//ft_printf("%s", grep_env(data, "SHLVL="));
	while (tmp)
	{
		free(tmp);
		tmp = readline(PROMPT);
		add_history(tmp);
		if (tmp)
		{
			if (ft_strncmp(tmp, "echo", 4) == 0)
				ft_echo(&tmp[5], 1);
			else
				ft_printf("%s: command not found\n", tmp);
		}
	}
	free(tmp);
}
