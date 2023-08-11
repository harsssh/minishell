/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:52:47 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/20 09:05:04 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;
	size_t	bytes;

	bytes = count * size;
	if (size != 0 && bytes / size != count)
		return (NULL);
	buf = malloc(bytes);
	if (!buf)
		return (NULL);
	return (ft_memset(buf, 0, bytes));
}
