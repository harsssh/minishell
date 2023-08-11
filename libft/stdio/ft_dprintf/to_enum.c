/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_enum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:22:42 by kemizuki          #+#    #+#             */
/*   Updated: 2023/05/24 14:23:23 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

t_spec	to_specifier(char c)
{
	if (c == 'c')
		return (CHAR);
	if (c == 's')
		return (STRING);
	if (c == 'd' || c == 'i')
		return (DECIMAL);
	if (c == 'u')
		return (U_DECIMAL);
	if (c == 'x')
		return (HEX);
	if (c == 'X')
		return (HEX_UP);
	if (c == 'p')
		return (POINTER);
	if (c == '%')
		return (PERCENT);
	return (UNKNOWN_SPEC);
}

t_flag	to_flag(char c)
{
	if (c == '-')
		return (HYPHEN);
	else if (c == '+')
		return (PLUS);
	else if (c == ' ')
		return (SPACE);
	else if (c == '#')
		return (HASH);
	else if (c == '0')
		return (ZERO);
	return (UNKNOWN_FLAG);
}
