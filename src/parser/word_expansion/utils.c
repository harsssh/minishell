/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:48:14 by smatsuo           #+#    #+#             */
/*   Updated: 2023/10/20 13:48:48 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*join_char(char *str, const char **word)
{
	char	s[2];
	char	*res;

	s[0] = **word;
	s[1] = '\0';
	res = ft_strjoin(str, s);
	free(str);
	(*word)++;
	return (res);
}
