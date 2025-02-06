/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:12:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/06 14:34:58 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *str, int has_newline)
{
	int		i;
	int		len;
	char	*tmp;
	char	*sub;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len = ft_strcharindex(&str[i], ' ');
			sub = ft_substr(str, i + 1, len - 1);
			tmp = getenv(sub);
			if (tmp)
				write(1, tmp, ft_strlen(tmp));
			i += len - 1;
		}
		else
			write(1, &str[i], 1);
		i++;
	}
	if (has_newline)
		ft_putchar_fd('\n', 1);
}
