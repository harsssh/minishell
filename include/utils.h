/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:34:27 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/11 19:12:58 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "ft_list.h"

// fs.c
bool	is_existing_directory(const char *path);

// list.c
// `f` must not fail (e.g. malloc failure)
char	**list_to_string_array(t_list *list, char *(*f)(void *data));

#endif
