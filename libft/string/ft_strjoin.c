/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:33:56 by kemizuki          #+#    #+#             */
/*   Updated: 2023/06/15 03:35:01 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buf;
	size_t	buf_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	buf_len = 1;
	if (s1 != NULL)
		buf_len += ft_strlen(s1);
	if (s2 != NULL)
		buf_len += ft_strlen(s2);
	buf = ft_calloc(buf_len, sizeof(char));
	if (buf == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strlcat(buf, s1, buf_len);
	if (s2 != NULL)
		ft_strlcat(buf, s2, buf_len);
	return (buf);
}
