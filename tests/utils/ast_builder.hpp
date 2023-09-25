#pragma once

#include <cstring>
#include <stack>

extern "C" {
#include "ast.h"
};

class ASTBuilder {
public:
	explicit ASTBuilder(t_ast_node_type rootType);

	// 引数を現在のノードに追加
	ASTBuilder &addArgument(const char *arg);

	// リダイレクトを現在のノードに追加
	ASTBuilder &addRedirect(t_redirect_type type, const char *filename);

	// ノードの作成
	// 既にあったら何もしない
	ASTBuilder &addLeft(t_ast_node_type type);
	ASTBuilder &addRight(t_ast_node_type type);

	// 子に移動
	// なければ何もしない
	ASTBuilder &moveToLeft();
	ASTBuilder &moveToRight();
	// 作成 & 移動
	ASTBuilder &moveToLeft(t_ast_node_type type);
	ASTBuilder &moveToRight(t_ast_node_type type);

	// 現在のノードを親ノードに移動
	ASTBuilder &moveToParent();

	// 現在のノードをルートに移動
	ASTBuilder &moveToRoot();

	// 完成したASTを取得
	t_ast_node *getAST() const;

	bool operator==(t_ast_node *node) const;

private:
	t_ast_node *ast;                          // Root of the AST
	t_ast_node *current;                      // Current node being operated on
	std::stack<t_ast_node *> parentNodes;     // Stack for tracking parent nodes

	// ノードを作成するヘルパー関数
	static t_ast_node *createNode(t_ast_node_type type);
};
