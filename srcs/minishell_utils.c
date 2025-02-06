/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:54:44 by maregnie          #+#    #+#             */
/*   Updated: 2025/02/06 16:22:53 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**grep_var(char **envp, char *to_grep)
{
	char	**paths;
	int		i;

	paths = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], to_grep, ft_strlen(to_grep)) == 0)
		{
			paths = ft_split(&envp[i][ft_strlen(to_grep)], ':');
			break;
		}
	}
	return (paths);
}
