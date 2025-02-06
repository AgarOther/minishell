/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maregnie <maregnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:37:32 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/06 17:12:44 by maregnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data
{
	char	**envp;
	char	**cmds;
	int		**pipes;
	int		in;
	int		out;
	pid_t	*pids;
}				t_data;

#endif
