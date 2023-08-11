/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:18:10 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/18 15:34:18 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	char	*res;

	chr = c;
	res = NULL;
	while (*s)
	{
		if (*s == chr)
			res = (char *)s;
		s++;
	}
	if (*s == chr)
		res = (char *)s;
	return (res);
}
