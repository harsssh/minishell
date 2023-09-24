/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:15:40 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/19 22:18:16 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	destroy_string_array(char **array)
{
	char	**cur;

	if (array == NULL)
		return ;
	cur = array;
	while (*cur)
	{
		free(*cur);
		++cur;
	}
	free(array);
}
