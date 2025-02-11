/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:03 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/11 16:16:42 by scraeyme         ###   ########.fr       */
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
int		ft_pwd(t_data *data);
void	ft_cd(t_data *data);
void	ft_env(t_data *data);

// Utils
char	**grep_var(char **envp, char *to_grep);
int		free_data(t_data *data, int free_envp);
t_data	*fill_data(t_data *data, int i);
t_data	*setup_data(char **envp);

// Tokens
t_token	*ft_newtoken(char *arg, t_TYPE type);
void	ft_tokenadd_back(t_token **token, t_token *new);
void	ft_tokenclear(t_token **token);
int		ft_tokencountpipes(t_token *tokens);
t_token	*get_tokens(t_data *data);

// Parsing
int		cmd_valid(char *str);
void	get_parsed_input(t_data **data, t_token *tokens);
void	split_cmds(t_data *data);
int		has_valid_input(t_token *tokens);

// Debug --------------------------------------------------------------------------------
void	print_tokens(t_token *tokens);

#endif
