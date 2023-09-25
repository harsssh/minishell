/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_ast.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatsuo <smatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:05:02 by smatsuo           #+#    #+#             */
/*   Updated: 2023/09/25 19:05:09 by smatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
#include "ast.h"
};

// ASTを比較する再帰関数
bool compareASTNodes(const t_ast_node *node1, const t_ast_node *node2);
