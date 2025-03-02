/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:37:32 by maregnie          #+#    #+#             */
/*   Updated: 2025/03/02 13:22:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_type
{
	COMMAND,
	ARG,
	PIPE,
	INFILE,
	OUTFILE,
	HEREDOC,
	APPENDFILE,
	UNDEFINED
}	t_TYPE;

typedef struct s_token
{
	char			*arg;
	t_TYPE			type;
	struct s_token	*next;
}			t_token;

typedef struct s_data
{
	char	**envp;
	char	*input;
	int		**pipes;
	int		in;
	int		out;
	int		out_tmp;
	int		nb_cmds;
	int		exit_code;
	int		cmd_count;
	pid_t	*pids;
	t_list	*list;
	t_token	*tokens;
}				t_data;

#endif
