/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:35:21 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/25 04:36:32 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INTERNAL_H
# define EXEC_INTERNAL_H

# include "ast.h"
# include "context.h"
# include <unistd.h>

# define ERR_PIPE "pipe error"
# define ERR_AMBIGUOUS_REDIRECT "ambiguous redirect"
# define ERR_CMD_NOT_FOUND	"command not found"

# define EXIT_OTHER_ERR		126
# define EXIT_CMD_NOT_FOUND 127

typedef struct s_pipeline_info
{
	int			fd_in;
	int			fd_out;
	pid_t		last_command_pid;
	t_list		*fd_close_list;
}				t_pipeline_info;

// pipeline_info.c
t_pipeline_info	*new_pipeline_info(void);
void			destroy_pipeline_info(t_pipeline_info *info);
void			push_fd_close_list(t_pipeline_info *info, int fd);

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
int				wait_children(pid_t last_command_pid);

// utils_internal.c
bool			is_in_pipeline(t_pipeline_info *info);
void			wait_children_and_set_exit_status(t_context *ctx,
					pid_t last_command_pid);

// configure_io.c
int				configure_io(t_context *ctx, t_pipeline_info *info,
					t_list *redirect_list);

#endif
