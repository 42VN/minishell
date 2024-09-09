/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:18:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/19 00:46:12 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_parse_format(const char *format, va_list ap)
{
	t_printf	s;
	size_t		i;

	i = 0;
	ft_printf_init(&s);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			ft_print_format(&s, format[++i], ap);
		else
			ft_add_to_struct(&s, format[i]);
		if (s.err == 1)
		{
			free(s.str);
			return (-1);
		}
		i++;
	}
	write(1, s.str, s.index);
	free(s.str);
	return (s.index);
}

static int	ft_parse_format_fd(int fd, const char *format, va_list ap)
{
	t_printf	s;
	size_t		i;

	i = 0;
	ft_printf_init(&s);
	if (s.str == NULL)
		return (-1);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			ft_print_format(&s, format[++i], ap);
		else
			ft_add_to_struct(&s, format[i]);
		if (s.err == 1)
		{
			free(s.str);
			return (-1);
		}
		i++;
	}
	s.write_count = write(fd, s.str, s.index);
	free(s.str);
	if (s.write_count != s.index)
		return (-1);
	return (s.index);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_parse_format(format, ap);
	va_end(ap);
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_parse_format_fd(fd, format, ap);
	va_end(ap);
	return (count);
}
