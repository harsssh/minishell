/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:17:43 by kemizuki          #+#    #+#             */
/*   Updated: 2023/12/03 16:22:53 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include <stdlib.h>
#include <unistd.h>

#define XMALLOC_EXIT_STATUS 2

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_dprintf(STDERR_FILENO, "xmalloc: cannot allocate %lu bytes\n", size);
		exit(XMALLOC_EXIT_STATUS);
	}
	return (ptr);
}
