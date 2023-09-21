/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:10:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/21 20:11:47 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <unistd.h>

bool	is_in_pipeline(t_pipeline_info *info)
{
	return (!(info->fd_in == STDIN_FILENO && info->fd_out == STDOUT_FILENO));
}
