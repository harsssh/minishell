/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:26:29 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERNAL_H
# define BUILTINS_INTERNAL_H

# include "context.h"

# define ERR_TOO_MANY_ARG "too many arguments"
# define ERR_NUM_REQUIRED "numeric argument required"
# define ERR_WRITE "write error"
# define ERR_NOT_IMPL "not implemented"
# define ERR_STDOUT "stdout"
# define ERR_IDENTIFIER "not a valid identifier"

typedef enum e_get_opt_status
{
	END_OF_ARG,
	END_OF_OPTIONS,
	ILLEGAL_OPTION,
	INITIALIZE,
}					t_get_opt_status;

void				perror_builtin(t_context *ctx, const char *cmd,
						const char *prefix);
void				print_error_builtin(t_context *ctx, const char *cmd,
						const char *loc, const char *msg);
void				print_quoted_error_builtin(t_context *ctx, const char *cmd,
						const char *loc, const char *msg);
void				print_simple_error_builtin(t_context *ctx, const char *cmd,
						const char *msg);

void				init_get_next_option(void);
t_get_opt_status	get_next_option(char *arg, const char *optstring);
char				**ignore_options(char **args);
char				*get_working_directory(t_context *ctx, char *for_whom);
void				sync_working_directory(t_context *ctx, char *for_whom);

#endif
