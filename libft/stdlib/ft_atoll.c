/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:47:22 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/05 09:38:43 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"
#include <errno.h>
#include <limits.h>

static int	read_up_to_sign(const char **s)
{
	while (**s && ft_isspace(**s))
		(*s)++;
	if (**s && **s == '-')
	{
		(*s)++;
		return (-1);
	}
	if (**s && **s == '+')
		(*s)++;
	return (1);
}

static int	is_overflow(int sign, unsigned long long num, unsigned long long x)
{
	unsigned long long	limit;

	if (sign > 0)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	return (limit / 10 < num || limit - num * 10 < x);
}

long long	ft_atoll(const char *str)
{
	int					sign;
	unsigned long long	num;
	unsigned long long	x;

	num = 0;
	sign = read_up_to_sign(&str);
	while (*str && ft_isdigit(*str))
	{
		x = *str++ - '0';
		if (is_overflow(sign, num, x))
		{
			errno = ERANGE;
			if (sign > 0)
				return (LLONG_MAX);
			return (LLONG_MIN);
		}
		num = num * 10 + x;
	}
	return ((long long)(sign * num));
}
