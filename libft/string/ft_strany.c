/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strany.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 00:42:00 by kemizuki          #+#    #+#             */
/*   Updated: 2023/07/31 00:42:00 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

int	ft_strany(const char *str, int (*f)(int))
{
	if (str == NULL || f == NULL)
		return (0);
	while (*str)
	{
		if (f(*str))
			return (1);
		str++;
	}
	return (0);
}
