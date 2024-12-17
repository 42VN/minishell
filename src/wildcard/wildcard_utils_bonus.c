/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:19 by hitran            #+#    #+#             */
/*   Updated: 2024/12/17 12:19:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_loop(const char **f, const char **p, const char **star,
	const char **match)
{
	while (**f)
	{
		if (**p == '*')
		{
			*star = (*p)++;
			*match = *f;
		}
		else if (**p == **f)
		{
			(*p)++;
			(*f)++;
		}
		else if (*star)
		{
			*p = *star + 1;
			(*match)++;
			*f = *match;
		}
		else
			return (0);
	}
	return (1);
}

int	is_match(const char *file, const char *pattern)
{
	const char	*f;
	const char	*p;
	const char	*star;
	const char	*match;

	f = file;
	p = pattern;
	star = NULL;
	match = f;
	if (!match_loop(&f, &p, &star, &match))
		return (0);
	while (*p == '*')
		p++;
	if (*p)
		return (0);
	return (1);
}

int	print_malloc_error(void)
{
	ft_printf_fd(STDERR_FILENO, "minishell: memory allocation failed!\n");
	return (EXIT_FAILURE);
}