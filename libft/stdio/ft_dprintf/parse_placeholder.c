/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_placeholder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:55:18 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 14:59:31 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include "ft_ctype.h"
#include "ft_stdlib.h"
#include <stdbool.h>

static char	*parse_flags(t_placeholder *p, const char *s)
{
	t_flag	f;

	if (*s == '\0')
		return ((char *)s);
	f = to_flag(*s);
	if (f == UNKNOWN_FLAG)
		return ((char *)s);
	p->flags |= f;
	return (parse_flags(p, s + 1));
}

static char	*parse_width(t_placeholder *p, const char *s)
{
	if (*s == '\0')
		return ((char *)s);
	p->exist_width = ft_isdigit(*s);
	if (p->exist_width)
	{
		p->width = ft_atol(s);
		while (*s && ft_isdigit(*s))
			s++;
	}
	return ((char *)s);
}

static char	*parse_precision(t_placeholder *p, const char *s)
{
	if (*s != '.')
		return ((char *)s);
	s++;
	p->exist_precision = ft_isdigit(*s);
	if (p->exist_precision)
	{
		p->precision = ft_atol(s);
		while (*s && ft_isdigit(*s))
			s++;
	}
	return ((char *)s);
}

static char	*parse_specifier(t_placeholder *p, const char *s)
{
	if (*s)
	{
		p->specifier = to_specifier(*s);
		if (p->specifier != UNKNOWN_SPEC)
			s++;
	}
	else
		p->specifier = UNKNOWN_SPEC;
	return ((char *)s);
}

/**
 * parse a placeholder at the beginning of a given string
 * @return a pointer to the string after the placeholder
 */
char	*parse_placeholder(t_placeholder *p, const char *s)
{
	if (*s != '%')
		return ((char *)s);
	s++;
	p->flags = 0;
	p->precision = 0;
	p->exist_width = false;
	p->exist_precision = false;
	s = parse_flags(p, s);
	s = parse_width(p, s);
	s = parse_precision(p, s);
	s = parse_specifier(p, s);
	return ((char *)s);
}
