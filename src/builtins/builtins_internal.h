/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:19:23 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/16 12:43:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERNAL_H
# define BUILTINS_INTERNAL_H

# include "context.h"
# include "utils.h"

# define ERR_TOO_MANY_ARG	"too many arguments"
# define ERR_NUM_REQUIRED	"numeric argument required"
# define ERR_WRITE			"write error"
# define ERR_NOT_IMPL		"not implemented"
# define ERR_STDOUT			"stdout"
# define ERR_IDENTIFIER		"not a valid identifier"

typedef enum e_getopt_status
{
	OPT_SUCCESS,
	OPT_ILLEGAL,
	OPT_END_OF_ARG,
	OPT_END_OF_OPTIONS
}					t_getopt_status;

void				init_get_next_option(void);
t_getopt_status		get_next_option(const char *arg,
						const char *valid_options, char *option);
const char			**ignore_options(const char **args);

#endif
