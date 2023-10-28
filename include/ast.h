/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemizuki <kemizuki@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:41:51 by kemizuki          #+#    #+#             */
/*   Updated: 2023/10/28 15:28:23 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "context.h"

/**
 * @brief Enumeration of AST node types
 *
 * - N_COMMAND: Regular command node
 * - N_AND: Logical AND operator node (&&)
 * - N_OR: Logical OR operator node (||)
 * - N_PIPE: Pipe operator node (|)
 */
typedef enum e_ast_node_type
{
	N_SUBSHELL,
	N_COMMAND,
	N_AND,
	N_OR,
	N_PIPE,
	N_SEMICOLON,
}	t_ast_node_type;

/**
 * @brief Structure representing nodes in an Abstract Syntax Tree (AST)
 *
 * - type: The type of the AST node (e.g., N_COMMAND for a regular command)
 * - left: Pointer to the left child node in the AST
 * - right: Pointer to the right child node in the AST
 * - argv: An array of strings representing the arguments of the command
 * - redirects: A linked list of redirection information associated with the node
 */
typedef struct s_ast_node
{
	t_ast_node_type		type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_list				*argv;
	t_list				*redirects;
}	t_ast_node;

/**
 * @brief Enumeration of redirection types
 *
 * - REDIRECT_IN: Represents input redirection
 * - REDIRECT_OUT: Represents output redirection
 * - REDIRECT_APPEND: Represents append output redirection
 * - REDIRECT_HERE_DOC: Represents here document redirection
 */
typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HERE_DOC,
}	t_redirect_type;

/**
 * @brief Structure representing redirection information
 *
 * - type: The type of redirection (e.g., REDIRECT_IN for input redirection)
 * - filename: The name of the file associated with the redirection
 */
typedef struct s_redirect
{
	t_redirect_type	type;
	char			*filename;
}	t_redirect;

int			execute_ast(t_context *ctx, t_ast_node *ast);

t_ast_node	*new_ast_node(t_ast_node_type type,
				t_ast_node *left, t_ast_node *right);
t_redirect	*new_redirect(t_redirect_type type, char *filename);
void		destroy_node(t_ast_node *node);
void		destroy_redirect(t_redirect *redirect);
t_list		*get_node_argv(t_ast_node *node);
t_list		*get_node_redirects(t_ast_node *node);
int			add_node_argv(t_ast_node *node, char *arg);
int			add_node_redirect(t_ast_node *node, t_redirect *redirect);
void		set_node_redirects(t_ast_node *node, t_list *redirects);
void		set_redirect_filename(t_redirect *redirect, char *filename);
void		set_node_argv(t_ast_node *node, t_list *argv);
int			append_node_argv(t_ast_node *node, t_list *words);

#endif
