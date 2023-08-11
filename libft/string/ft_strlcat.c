/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:10:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/18 15:03:49 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	dlen = ft_strnlen(dst, dstsize);
	slen = ft_strlen(src);
	if (dlen == dstsize)
		return (slen + dstsize);
	if (slen < dstsize - dlen)
		ft_memcpy(dst + dlen, src, slen + 1);
	else
	{
		ft_memcpy(dst + dlen, src, dstsize - dlen - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dlen + slen);
}
