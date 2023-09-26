/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_internal.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:53:22 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/27 00:09:26 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_INTERNAL_H
# define WORD_EXPANSION_INTERNAL_H

# include "context.h"

char	*expand_parameter(char *word, t_context *ctx);

#endif
