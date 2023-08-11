/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:07:46 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/23 18:54:21 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include <stdlib.h>

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static size_t	count_width(unsigned int n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	store_digit(unsigned int n, char *buf, size_t len)
{
	if (n == 0)
	{
		buf[0] = '0';
		return ;
	}
	buf[len--] = '\0';
	while (n && len--)
	{
		buf[len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*buf;
	unsigned int	num;
	size_t			buf_len;

	num = ft_abs(n);
	buf_len = count_width(num) + 1;
	if (n < 0)
		buf_len++;
	buf = ft_calloc(buf_len, sizeof(char));
	if (buf == NULL)
		return (NULL);
	if (n < 0)
	{
		buf[0] = '-';
		store_digit(num, buf + 1, buf_len - 1);
	}
	else
		store_digit(num, buf, buf_len);
	return (buf);
}
