/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:03 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/07 15:59:42 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Defines
# define PROMPT "minicraquotte> "

// Includes S-Lib
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// Includes Project
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../libft/ft_printf/includes/ft_printf.h"

// Includes Minishell
# include "struct.h"

// Built-ins
void	ft_echo(char *str, int has_newline);

// Utils
char	**grep_var(char **envp, char *to_grep);
int		free_data(t_data *data, int free_envp);
t_data	*fill_data(t_data *data, int i);
t_data	*setup_data(char **envp);

// Parsing
int		cmd_valid(char *str);

#endif
