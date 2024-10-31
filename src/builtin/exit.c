/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:41:44 by hitran            #+#    #+#             */
/*   Updated: 2024/10/31 15:22:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

int	only_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
		if (!is_number(s[i++]))
			return (0);
	return (1);
}

long long	ft_atoll(const char *nptr)
{
	long long	nb;
	int			mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}

int	is_long(char *argv)
{
	if (ft_strlen(argv) > 20
		|| ft_atoll(argv) > LONG_MAX
		|| ft_atoll(argv) < LONG_MIN)
		return (0);
	return (1);
}

long long	exit_status_calculator(char *token)
{
	long long	nb;

	nb = ft_atoll(token);
	while (nb < 0)
		nb = 256 + nb;
	return (nb);
}

int	builtin_exit(t_shell *shell, char **token)
{
	int error_num;
	
	if (token[1] && (!only_number(token[1]) || !is_long(token[1])))
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, token[1], ft_strlen(token[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		update_status(2);
	}
	else if (token[1] && token[2])
	{
		shell_cleanup(shell);
		exit (builtin_error("exit\n", 1));
	}
	else
	{
		error_num = -1;
		if (token[1] && token[1][0])
			error_num = exit_status_calculator(token[1]);
		write(STDERR_FILENO, "exit\n", 5);
		update_status(error_num);
		shell_cleanup(shell);
		exit(error_num);
	}
	
}
