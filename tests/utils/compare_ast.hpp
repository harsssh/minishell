extern "C" {
#include "ast.h"
};

// ASTを比較する再帰関数
bool CompareASTNodes(const t_ast_node *node1, const t_ast_node *node2);
