/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:41:44 by hitran            #+#    #+#             */
/*   Updated: 2024/11/05 10:53:16 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_numberic(char *s)
{
	long	number;
	long	check;
	int		sign;

	number = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
		s++;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (1);
		check = number * 10 + *s - '0';
		if (check / 10 != number)
			return (1);
		number = check;
		s++;
	}
	return (0);
}

long	ft_atol(const char *s)
{
	long	number;
	long	check;
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
	{
		check = number * 10 + *s++ - '0';
		if (check / 10 != number)
			return (2);
		number = check;
	}
	return (number * sign);
}

long long	to_8bits(long nb)
{
	nb %= 256;
	if (nb < 0)
		nb += 256;
	return (nb);
}

int exit_error(t_shell *shell, char *token, char *message, int error_num)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	if (token)
	{
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);	
	update_status(shell, error_num);
	shell_cleanup(shell);
	return (error_num);
}

int	builtin_exit(t_shell *shell, char **token)
{
	// int error_num;
	
	write(STDERR_FILENO, "exit\n", 5);
	if (token[1] && not_numberic(token[1]))
		exit (exit_error(shell, token[1], "numeric argument required", 2));
	else if (token[1] && token[2])
		return (exit_error(shell, NULL, "too many arguments", 1));
	else
	{
		// error_num = 0;
		if (token[1] && token[1][0])
			shell->exitcode = to_8bits(ft_atol(token[1]));
			// error_num = to_8bits(ft_atol(token[1]));
		shell_cleanup(shell);
		exit(shell->exitcode);
		// exit(error_num);
	}
	
}
