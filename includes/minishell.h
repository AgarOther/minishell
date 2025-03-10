/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:41:03 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/09 02:30:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Defines - Misc
# define PROMPT "minishlel> "
# define TMP_FILEPATH "/tmp/.minishlel"

// Defines - Errors
# define TOO_MANY_ARGS "Error: Too many arguments."
# define NUM_ARG_REQUIRED "Error: Numeric argument required."
# define INVALID_INFILE "Error: Invalid infile."
# define INVALID_OUTFILE "Error: Invalid outfile."
# define INVALID_SYNTAX "Error: Invalid syntax."
# define INVALID_COMMAND "Error: Command not found."
# define INVALID_PARAM "Error: Invalid parameter name."
# define NOT_A_DIR "Error: Not a directory."
# define BAD_ASSIGNMENT "Error: Bad assignment."
# define NO_SUCH_FILE_DIR "Error: No such file or directory."
# define INVALID_IDENTIFIER "Error: Not a valid identifier."
# define IS_DIR "Error: Is a directory."
# define PERM_DENIED "Error: Permission denied."
# define WARN_EOF "Warning: End Of File (EOF) detected instead of delimiter."

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
# include <limits.h>
# include <dirent.h>
# include <errno.h>

// Includes Project
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../libft/ft_printf/includes/ft_printf.h"

// Includes Minishell
# include "struct.h"

// Global Variable
extern int	g_signal;

// Built-ins
void	ft_echo(t_data **data, char *str);
void	ft_pwd(t_data **data);
void	ft_cd(t_data **data, char **cmd, char *pwd);
void	ft_env(t_data **data);
void	ft_exit(t_data **data, char **cmd, unsigned char code, long long res);
void	ft_unset(t_data **data, char **vars);
void	ft_export(t_data **data, char **args);

// Execution
void	handle_commands(t_data *data);
void	process_tokens(t_data **data);
pid_t	forkit(t_data *data, char **cmds, char *raw_cmd);
int		ft_execve(char *path, char **cmd, t_data *data, char *raw_cmd);

// File handling
int		set_file_descriptors(t_data **data, t_token *tokens);

// Parsing
char	*expand_command(t_data *data, char *command, int i, int j);
void	ft_heredoc(char *limiter, t_data **data, int quoted);
int		get_expanded(t_data *data, char *value, char *new);
int		get_sepindex(char *str);
int		get_alloc_size(t_data *data, char *command, int i, int value);

// Signals
void	intercept_signals(void);
void	prevent_signals(void);
void	handle_forkit_signals(int sig);

// Tokens
t_token	*ft_newtoken(char *arg, t_type type, int need_alloc);
void	ft_tokenadd_back(t_token **token, t_token *new);
void	ft_tokenclear(t_token **token);
int		ft_tokencount(t_token *tokens, t_type type);
int		ft_tokensize(t_token *token);
void	get_tokens(t_data **data, int i);

// Utils - Commands
void	ft_strerror(t_data **data, int error, char *msg);
int		get_error_code(int status);
char	*get_cmd_path(char **envp, char *cmd, int i, char **paths);
char	*addquotes(char *str);

// Utils - Data
void	close_fd(t_data *data);
int		free_data(t_data *data, int free_envp);
t_data	*fill_data(t_data *data);
t_data	*setup_data(char **envp);

// Utils - Export
char	*rm_first_occur(char *arg, char c);
void	ft_lstprint_export(t_list *lst);
int		is_exportable(char *arg);
void	print_sorted(t_data *data);

// Utils - Minishell
void	safe_close(int fd);
void	update_env(t_list *lst, t_data **data);
void	free_pipes(t_data *data);
char	*grep_var_as_string(char **envp, char *to_grep);
char	**grep_var(char **envp, char *to_grep);

// Utils - Misc
char	*get_tmp_filepath(int cmd_count);
void	unlink_heredocs(t_data *data);
int		is_blacklist(char c);
int		is_expandable(char c);
int		is_directory(char *path);

// Utils - Parsing
char	*delete_quotes(char *str, int needs_free, int i);
int		has_invalid_quotes(char *str);
t_list	*get_env_as_lst(t_data *data);
int		has_invalid_syntax(t_data *data);

// Utils - Tokenizer
t_list	*ft_list_remove_if(char *var, t_list *current, int free_var);
t_type	get_type(char *str, int *i);
int		get_token_length(char *str);
int		is_token(char c);

#endif
