/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:10:18 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/25 02:54:35 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_internal.h"
#include <stdlib.h>
#include <unistd.h>

t_pipeline_info	*new_pipeline_info(void)
{
	t_pipeline_info	*info;

	info = malloc(sizeof(t_pipeline_info));
	if (info == NULL)
		return (NULL);
	info->fd_in = STDIN_FILENO;
	info->fd_out = STDOUT_FILENO;
	info->fd_close_list = ft_list_create();
	if (info->fd_close_list == NULL)
	{
		destroy_pipeline_info(info);
		return (NULL);
	}
	return (info);
}

void	destroy_pipeline_info(t_pipeline_info *info)
{
	ft_list_destroy(info->fd_close_list, free);
	free(info);
}

void	push_fd_close_list(t_pipeline_info *info, int fd)
{
	int	*fd_ptr;

	fd_ptr = malloc(sizeof(int));
	*fd_ptr = fd;
	ft_list_push_back(info->fd_close_list, fd_ptr);
}
