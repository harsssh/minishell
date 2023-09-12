/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:41:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/12 18:11:35 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum e_ast_node_type
{
	N_COMMAND,
	N_SEQUENCE,
	N_AND,
	N_OR,
	N_PIPE,
	N_REDIRECT_IN,
	N_REDIRECT_OUT,
	N_REDIRECT_APPEND,
	N_REDIRECT_HERE_DOC
}	t_ast_node_type;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	struct ast_node	*left;
	struct ast_node	*right;
	char			**argv;
	char			*filename;
}	t_ast_node;

#endif
