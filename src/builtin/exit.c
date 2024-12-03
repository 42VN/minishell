/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:41:44 by hitran            #+#    #+#             */
/*   Updated: 2024/12/03 19:22:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_numberic(char *s)
{
	if (!s[0])
		return (1);
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (1);
		s++;
	}
	return (0);
}

long	ft_atol(const char *s)
{
	long	number;
	int		sign;

	number = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		number = number * 10 + *s++ - '0';
	return (number * sign);
}

long long	to_8bits(long nb)
{
	nb %= 256;
	if (nb < 0)
		nb += 256;
	return (nb);
}

void	exit_error(t_shell *shell, char *token, char *message, int error_num)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (token)
	{
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	update_status(shell, error_num);
}

void	builtin_exit(t_shell *shell, char **token)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (token[1] && not_numberic(token[1]))
	{
		exit_error(shell, token[1], "numeric argument required", 2);
		free_all(shell);
		exit (shell->exitcode);
	}
	else if (token[1] && token[2])
		exit_error(shell, NULL, "too many arguments", 1);
	else
	{
		if (token[1] && token[1][0])
			shell->exitcode = to_8bits(ft_atol(token[1]));
		free_all(shell);
		exit(shell->exitcode);
	}
}
