#include <cstring>

extern "C" {
#include "ast.h"
};

// ASTを比較する再帰関数
bool compareASTNodes(const t_ast_node *node1, const t_ast_node *node2)
{
	if (node1 == nullptr && node2 == nullptr)
		return true;
	if (node1 == nullptr || node2 == nullptr)
		return false;

	if (node1->type != node2->type)
		return false;

	if (!(node1->argv == nullptr && node2->argv == nullptr))
	{
		if (node1->argv == nullptr || node2->argv == nullptr)
			return false;

		if (node1->argv->size != node2->argv->size)
			return false;

		t_node *it1 = node1->argv->head;
		t_node *it2 = node2->argv->head;

		while (it1 != nullptr && it2 != nullptr)
		{
			char *arg1 = static_cast<char *>(it1->data);
			char *arg2 = static_cast<char *>(it2->data);

			if (std::strcmp(arg1, arg2) != 0)
				return false;

			it1 = it1->next;
			it2 = it2->next;
		}
	}

	if (!(node1->redirects == nullptr && node2->redirects == nullptr))
	{
		if (node1->redirects == nullptr || node2->redirects == nullptr)
			return false;

		if (node1->redirects->size != node2->redirects->size)
			return false;

		t_node *rit1 = node1->redirects->head;
		t_node *rit2 = node2->redirects->head;

		while (rit1 != nullptr && rit2 != nullptr)
		{
			t_redirect *redir1 = static_cast<t_redirect *>(rit1->data);
			t_redirect *redir2 = static_cast<t_redirect *>(rit2->data);

			if (redir1->type != redir2->type || std::strcmp(redir1->filename, redir2->filename) != 0)
				return false;

			rit1 = rit1->next;
			rit2 = rit2->next;
		}
	}

	return compareASTNodes(node1->left, node2->left) && compareASTNodes(node1->right, node2->right);
}
