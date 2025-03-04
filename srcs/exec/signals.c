/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:26:05 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/04 23:42:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_sig_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putendl_fd("Quit", 2);
}

void	get_cmd_sigquit(void)
{
	signal(SIGQUIT, cmd_sig_handler);
	signal(SIGINT, cmd_sig_handler);
}

static void	signal_handler(int sig)
{
	(void) sig;
	change_signal_value(130);
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
