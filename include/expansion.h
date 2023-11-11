/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:08:02 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/29 00:54:23 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "context.h"
# include "ft_list.h"

t_list	*expand_word(const char *word, t_context *ctx);
t_list	*expand_word_list(t_list *word_list, t_context *ctx);

#endif
