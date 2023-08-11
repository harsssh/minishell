/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:42:37 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 01:57:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "internal.h"
#include <stdarg.h>
#include <unistd.h>

static ssize_t	write_byte(int fd, unsigned char c)
{
	return (write(fd, &c, 1));
}

static ssize_t	write_string(int fd, const char *s)
{
	if (!s)
		return (write_string(fd, "(null)"));
	return (write(fd, s, ft_strlen(s)));
}

static size_t	print_placeholder(int fd, const t_placeholder ph, va_list *args)
{
	if (ph.specifier == CHAR)
		return (write_byte(fd, (unsigned char)(va_arg(*args, int))));
	if (ph.specifier == STRING)
		return (write_string(fd, va_arg(*args, char *)));
	if (ph.specifier == DECIMAL)
		return (ft_putnbr_base(fd, va_arg(*args, int), DECIMAL_BASE));
	if (ph.specifier == U_DECIMAL)
		return (ft_putunbr_base(fd, va_arg(*args, unsigned int), DECIMAL_BASE));
	if (ph.specifier == HEX)
		return (ft_putunbr_base(fd, va_arg(*args, unsigned int), HEX_BASE));
	if (ph.specifier == HEX_UP)
		return (ft_putunbr_base(fd, va_arg(*args, unsigned int), HEX_BASE_UP));
	if (ph.specifier == POINTER)
	{
		ft_putstr_fd("0x", STDOUT_FILENO);
		return (2 + ft_putunbr_base(fd, (uintptr_t)va_arg(*args, void *),
				HEX_BASE));
	}
	if (ph.specifier == PERCENT)
		return (write_byte(fd, '%'));
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list			args;
	t_placeholder	ph;
	size_t			len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format = parse_placeholder(&ph, format);
			len += print_placeholder(fd, ph, &args);
		}
		else
			len += write(fd, format++, 1);
	}
	va_end(args);
	return (len);
}
