#include "ast_builder.hpp"

ASTBuilder::ASTBuilder(t_ast_node_type rootType) : ast(createNode(rootType)), current(ast) {}

// 引数を現在のノードに追加
ASTBuilder &ASTBuilder::addArgument(const char *arg) {
	if (current->type != N_COMMAND) return *this; // Ensure we're adding arguments to command nodes only
	t_list *list = (current->argv) ? current->argv : ft_list_create();
	ft_list_push_back(list, strdup(arg));
	current->argv = list;
	return *this;
}

// リダイレクトを現在のノードに追加
ASTBuilder &ASTBuilder::addRedirect(t_redirect_type type, const char *filename) {
	if (current->type != N_COMMAND) return *this; // Ensure we're adding redirects to command nodes only
	auto *redirect = new t_redirect();
	redirect->type = type;
	redirect->filename = strdup(filename);
	t_list *list = (current->redirects) ? current->redirects : ft_list_create();
	ft_list_push_back(list, redirect);
	current->redirects = list;
	return *this;
}

// ノードの作成
ASTBuilder &ASTBuilder::addLeft(t_ast_node_type type) {
	if (!current->left) {
		current->left = createNode(type);
	}
	return *this;
}

ASTBuilder &ASTBuilder::addRight(t_ast_node_type type) {
	if (!current->right) {
		current->right = createNode(type);
	}
	return *this;
}

// 左の子に移動
ASTBuilder &ASTBuilder::moveToLeft() {
	if (!current->left) return *this;
	parentNodes.push(current);
	current = current->left;
	return *this;
}

ASTBuilder &ASTBuilder::moveToLeft(t_ast_node_type type) {
	if (!current->left) {
		addLeft(type);
	}
	return moveToLeft();
}

// 右の子に移動
ASTBuilder &ASTBuilder::moveToRight() {
	if (!current->right) return *this;
	parentNodes.push(current);
	current = current->right;
	return *this;
}

ASTBuilder &ASTBuilder::moveToRight(t_ast_node_type type) {
	if (!current->right) {
		addRight(type);
	}
	return moveToRight();
}

// 現在のノードを親ノードに移動
ASTBuilder &ASTBuilder::moveToParent() {
	if (!parentNodes.empty()) {
		current = parentNodes.top();
		parentNodes.pop();
	}
	return *this;
}

ASTBuilder &ASTBuilder::moveToRoot() {
	current = ast;
	parentNodes = std::stack<t_ast_node *>();
	return *this;
}

// 完成したASTを取得
t_ast_node *ASTBuilder::getAST() const {
	return ast;
}

// ノードを作成するヘルパー関数
t_ast_node *ASTBuilder::createNode(t_ast_node_type type) {
	auto *node = new t_ast_node();
	memset(node, 0, sizeof(t_ast_node)); // Initialize all members to 0/NULL
	node->type = type;
	return node;
}
