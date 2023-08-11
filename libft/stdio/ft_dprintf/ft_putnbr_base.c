/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:10:07 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 01:37:57 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "internal.h"
#include <unistd.h>

size_t	ft_putunbr_base(int fd, unsigned long long nbr, char *base)
{
	unsigned int	blen;
	size_t			len;

	blen = ft_strlen(base);
	if (nbr < blen)
		return (write(fd, base + nbr, 1));
	len = ft_putunbr_base(fd, nbr / blen, base);
	len += ft_putunbr_base(fd, nbr % blen, base);
	return (len);
}

size_t	ft_putnbr_base(int fd, long long nbr, char *base)
{
	unsigned int	blen;
	size_t			len;

	blen = ft_strlen(base);
	if (nbr >= 0)
		return (ft_putunbr_base(fd, nbr, base));
	ft_putchar_fd('-', fd);
	len = 1;
	if (nbr / blen != 0)
		len += ft_putunbr_base(fd, -(nbr / blen), base);
	len += ft_putunbr_base(fd, -(nbr % blen), base);
	return (len);
}
