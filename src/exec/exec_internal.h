/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/23 03:18:29 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "ast.h"
# include "context.h"
# include <unistd.h>

typedef struct s_pipeline_info
{
	int			fd_in;
	int			fd_out;
	t_list		*fd_close_list;
	t_list		*child_pid_list;
}				t_pipeline_info;

// pipeline_info.c
t_pipeline_info	*new_pipeline_info(void);
void			destroy_pipeline_info(t_pipeline_info *info);
void			push_fd_close_list(t_pipeline_info *info, int fd);
void			push_child_pid_list(t_pipeline_info *info, pid_t pid);

typedef int		(*t_ast_handler)(t_context *ctx, t_pipeline_info *info,
			t_ast_node *ast);

int				handle_command(t_context *ctx, t_pipeline_info *info,
					t_ast_node *ast);
int				handle_and_or(t_context *ctx, t_pipeline_info *info,
					t_ast_node *ast);
int				handle_pipeline(t_context *ctx, t_pipeline_info *info,
					t_ast_node *ast);

// execvp.c
int				internal_execvp(t_context *ctx, t_list *arg_list);

// execute_ast.c
int				execute_ast_impl(t_context *ctx, t_pipeline_info *info,
					t_ast_node *ast);

// wait_children.c
void			wait_children(t_context *ctx, t_list *child_pid_list);

// utils_internal.c
bool			is_in_pipeline(t_pipeline_info *info);

// configure_io.c
void configure_io(t_pipeline_info *info, t_list *redirect_list);

#endif
