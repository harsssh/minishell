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

// /bin/echo
TEST_F(TestExecuteAST, echo) {
	auto *ast = ASTBuilder(N_COMMAND)
			.addArgument("/bin/echo").addArgument("hello").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello world\n");
}

// /usr/bin/true && /bin/echo success
TEST_F(TestExecuteAST, and_if) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("success")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "success\n");
}

// /usr/bin/false && /bin/echo success
// 実行されないことを確認
TEST_F(TestExecuteAST, and_if_false) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/false")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("success")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "");
}

// /usr/bin/false || /bin/echo failure
TEST_F(TestExecuteAST, or_if) {
	auto *ast = ASTBuilder(N_OR)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/false")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("failure")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "failure\n");
}

// /usr/bin/true || /bin/echo failure
// 実行されないことを確認
TEST_F(TestExecuteAST, or_if_true) {
	auto *ast = ASTBuilder(N_OR)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("failure")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "");
}

// /usr/bin/true && /usr/bin/false || /bin/echo ok
TEST_F(TestExecuteAST, and_if_or_if) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_OR)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/false")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("ok")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "ok\n");
}

// /usr/bin/false || /usr/bin/true && /bin/echo ok
TEST_F(TestExecuteAST, or_if_and_if) {
	auto *ast = ASTBuilder(N_OR)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/false")
			.moveToParent()
			.moveToRight(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("ok")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "ok\n");
}

// /bin/echo hello | /bin/cat
TEST_F(TestExecuteAST, pipe) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/bin/echo").addArgument("hello")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/cat")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\n");
}

// /bin/echo hello | /bin/cat | /bin/cat
TEST_F(TestExecuteAST, pipe_pipe) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/bin/echo").addArgument("hello")
			.moveToParent()
			.moveToRight(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/bin/cat")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/cat")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\n");
}

// /bin/echo hello world | /bin/tr o O | /bin/rev
TEST_F(TestExecuteAST, echo_tr_rev_pipe) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/bin/echo").addArgument("hello world")
			.moveToParent()
			.moveToRight(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/tr").addArgument("o").addArgument("O")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/usr/bin/rev")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "dlrOw Olleh\n");
}
