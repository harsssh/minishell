/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 01:36:47 by kemizuki          #+#    #+#             */
/*   Updated: 2023/11/30 01:37:56 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "characters.h"
#include "utils.h"

bool	is_quote(int c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}
