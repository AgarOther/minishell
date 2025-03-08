/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 23:26:05 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 13:13:05 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	newline_on_signal(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
}

void	prevent_signals(void)
{
	signal(SIGQUIT, newline_on_signal);
	signal(SIGINT, newline_on_signal);
}

static void	signal_handler(int sig)
{
	(void) sig;
	g_signal = sig;
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
