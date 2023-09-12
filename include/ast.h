/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:41:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/09/12 18:17:24 by kemizuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/**
 * @brief Enumeration of AST node types
 * 
 * - N_COMMAND: Regular command node
 * - N_SEQUENCE: Sequence node (;) 
 * - N_AND: Logical AND operator node (&&)
 * - N_OR: Logical OR operator node (||)
 * - N_PIPE: Pipe operator node (|)
 * - N_REDIRECT_IN: Input redirection operator node (<)
 * - N_REDIRECT_OUT: Output redirection operator node (>)
 * - N_REDIRECT_APPEND: Append output redirection operator node (>>)
 * - N_REDIRECT_HERE_DOC: "Here document" redirection operator node (<<)
 */
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

/**
 * @brief Structure representing nodes in as Abstract Syntax Tree (AST)
 * 
 * - type: The type of the AST node (e.g., N_COMMAND for a regular command)
 * - left: Pointer to the left child node in the AST
 * - right: Pointer to the right child node in the AST
 * - argv: An array of strings representing the arguments of the command
 * - filename: The filename associated with the node for redirection 
 */
typedef struct s_ast_node
{
	t_ast_node_type	type;
	struct ast_node	*left;
	struct ast_node	*right;
	char			**argv;
	char			*filename;
}	t_ast_node;

#endif
