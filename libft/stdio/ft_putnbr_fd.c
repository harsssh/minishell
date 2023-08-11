/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:14:45 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/20 13:04:13 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

// n is in the range of int
static void	put_positive_number(unsigned int n, int fd)
{
	char			s[16];
	unsigned int	i;

	if (n == 0)
		ft_putchar_fd('0', fd);
	i = 0;
	while (n)
	{
		s[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (i--)
		ft_putchar_fd(s[i], fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		put_positive_number(-n, fd);
	}
	else
		put_positive_number(n, fd);
}
