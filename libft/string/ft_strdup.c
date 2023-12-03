/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:51:32 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/20 14:11:11 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	size_t	n;
	char	*buf;

	n = ft_strlen(src);
	buf = (char *) ft_xmalloc(n + 1);
	if (buf == NULL)
		return (NULL);
	ft_strlcpy(buf, src, n + 1);
	return (buf);
}
