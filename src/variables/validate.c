/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:22:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/08/18 19:22:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "variables.h"

static int	is_valid_character(int c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_identifier(const char *identifier)
{
	if (!(ft_isalpha(*identifier) || *identifier == '_'))
		return (0);
	return (ft_strall(identifier + 1, is_valid_character));
}
