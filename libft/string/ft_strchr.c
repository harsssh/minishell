/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:12:26 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/18 15:17:43 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	chr = c;
	while (*s && *s != chr)
		s++;
	if (*s == chr)
		return ((char *)s);
	return (NULL);
}
