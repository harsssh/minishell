#include <gtest/gtest.h>
#include "utils/ast_builder.hpp"

extern "C" {
#include "ast.h"
#include "variables_internal.h"
#include "ft_list.h"
}

class TestExecuteAST : public ::testing::Test {
protected:
	t_context ctx{};

	void SetUp() override {
		ctx = {.shell_name = "minishell", .variables = ft_list_create()};
		setvar(&ctx, "PATH", "/bin:/usr/bin", 1);
	}

	void TearDown() override {
		ft_list_destroy(ctx.variables, variable_destroy);
	}
};

// /bin/echo を実行
TEST_F(TestExecuteAST, echo) {
	auto *ast = ASTBuilder(N_COMMAND)
			.addArgument("/bin/echo").addArgument("hello").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello world\n");
}

// /bin/echo 42 && /bin/echo success を実行
TEST_F(TestExecuteAST, and_if) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/bin/echo").addArgument("42")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("success")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "42\nsuccess\n");
}
