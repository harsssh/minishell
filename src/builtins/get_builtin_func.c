/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:08:25 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/22 15:16:08 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ft_string.h"
#include "libft.h"

t_builtin_func	get_builtin_func(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtins_cd);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtins_export);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtins_echo);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (builtins_env);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtins_exit);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtins_pwd);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtins_unset);
	else
		return (NULL);
}
