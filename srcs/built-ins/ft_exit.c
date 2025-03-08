/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:14:58 by scraeyme          #+#    #+#             */
/*   Updated: 2025/03/08 00:46:22 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_llonglen(long long n)
{
	size_t	len;

	len = 1;
	n *= (1 + -2 * (n < 0));
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	sign_corresponds(char *nptr, long long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] && (nptr[i] == '+' || nptr[i] == '-' || nptr[i] == '0'))
		i++;
	if (ft_strchr(nptr, '-') && !ft_strcmp(&nptr[i], "9223372036854775808"))
		return (1);
	if ((ft_llonglen(n) != ft_strlen(&nptr[i]))
		|| (ft_strchr(nptr, '-') && n > 0))
		return (0);
	return (1);
}

static long long	ft_safe_atoll(const char *nptr, int *has_overflow, int i)
{
	long long	res;
	long long	neg;

	res = 0;
	neg = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] == '0')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if ((neg == -1 && i > 20) || (neg == 1 && i > 19)
		|| !sign_corresponds((char *)nptr, res * neg))
		*has_overflow = 1;
	return (res * neg);
}

static int	exit_and_free(t_data **data, char **cmd, char *tmp, int code)
{
	if (tmp)
		free(tmp);
	if (!ft_tokencount((*data)->tokens, PIPE))
		ft_putendl_fd("exit", 2);
	else
		return (0);
	free((*data)->raw_cmd);
	ft_tabfree(cmd, ft_tablen(cmd));
	close_fd(*data);
	free_data(*data, 1);
	exit(code);
	return (1);
}

void	ft_exit(t_data **data, char **cmd, unsigned char code, long long res)
{
	char			*tmp;
	int				has_overflow;

	if (!set_file_descriptors(data, (*data)->tokens) && (*data)->nb_cmds)
		return ;
	tmp = delete_quotes(cmd[1], 0, -1);
	has_overflow = 0;
	if ((ft_tablen(cmd) == 1 || ft_isfilled(cmd[1], ' ', NULL))
		&& !exit_and_free(data, cmd, tmp, (*data)->exit_code))
		return ;
	if (ft_tablen(cmd) > 2 && ft_stratoiable(cmd[1]))
	{
		free(tmp);
		return (ft_strerror(data, 1, TOO_MANY_ARGS));
	}
	if (tmp)
		res = ft_safe_atoll(tmp, &has_overflow, 0);
	if (has_overflow || !ft_stratoiable(tmp))
	{
		ft_strerror(data, 2, NUM_ARG_REQUIRED);
		code = 2;
	}
	if (!code)
		code = (unsigned char)res;
	exit_and_free(data, cmd, tmp, code);
}
