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
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// built-in echo
TEST_F(TestExecuteAST, builtin_echo) {
	auto *ast = ASTBuilder(N_COMMAND)
			.addArgument("echo").addArgument("hello").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello world\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
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
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// /usr/bin/true && echo success
// use built-in echo
TEST_F(TestExecuteAST, and_if_builtin) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("success")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "success\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
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
	ASSERT_EQ(ctx.last_exit_status, 1);
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
	ASSERT_EQ(ctx.last_exit_status, 0);
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
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// /usr/bin/true && /usr/bin/false || /bin/echo ok
TEST_F(TestExecuteAST, and_if_or_if) {
	auto *ast = ASTBuilder(N_OR)
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("ok")
			.moveToParent()
			.moveToLeft(N_AND)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/usr/bin/false")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "ok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// /usr/bin/false || /usr/bin/true && /bin/echo ok
TEST_F(TestExecuteAST, or_if_and_if) {
	auto *ast = ASTBuilder(N_AND)
			.moveToRight(N_COMMAND).addArgument("/bin/echo").addArgument("ok")
			.moveToParent()
			.moveToLeft(N_OR)
			.moveToLeft(N_COMMAND).addArgument("/usr/bin/false")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/usr/bin/true")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "ok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
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
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// /bin/echo hello | /bin/cat | /bin/cat
TEST_F(TestExecuteAST, pipe_pipe) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToRight(N_COMMAND).addArgument("/bin/cat")
			.moveToParent()
			.moveToLeft(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("/bin/echo").addArgument("hello")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("/bin/cat")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// 何も表示されないパターン
// ls | false
TEST_F(TestExecuteAST, pipe_false) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("ls")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("false")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "");
	ASSERT_EQ(ctx.last_exit_status, 1);
}

// echo hello world | tr o O | rev
// use only command name
TEST_F(TestExecuteAST, echo_tr_rev_pipe) {
	auto *ast = ASTBuilder(N_PIPE)
		.moveToRight(N_COMMAND).addArgument("rev")
		.moveToParent()
		.moveToLeft(N_PIPE)
		.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello world")
		.moveToParent()
		.moveToRight(N_COMMAND).addArgument("tr").addArgument("o").addArgument("O")
		.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "dlrOw Olleh\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// pipe and pipe
// echo hello | cat && echo world | cat
TEST_F(TestExecuteAST, pipe_and_pipe) {
	auto *ast = ASTBuilder(N_AND)
			.moveToLeft(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("cat")
			.moveToParent()
			.moveToParent()
			.moveToRight(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("world")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("cat")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\nworld\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// pipe or pipe
// true | false || echo ok | cat
TEST_F(TestExecuteAST, pipe_or_pipe) {
	auto *ast = ASTBuilder(N_OR)
			.moveToLeft(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("true")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("false")
			.moveToParent()
			.moveToParent()
			.moveToRight(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("ok")
			.moveToParent()
			.moveToRight(N_COMMAND).addArgument("cat")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "ok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// (echo hello)
TEST_F(TestExecuteAST, subshell_single_command) {
	auto *ast = ASTBuilder(N_SUBSHELL)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// (echo hello && echo world) | cat
TEST_F(TestExecuteAST, subshell_and_pipe) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToRight(N_COMMAND).addArgument("cat")
			.moveToParent() // N_PIPE
			.moveToLeft(N_SUBSHELL)
			.moveToLeft(N_AND)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_AND
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "hello\nworld\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}


// (echo hello | tr a-z A-Z) | cat
TEST_F(TestExecuteAST, subshell_pipe_inside) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToRight(N_COMMAND).addArgument("cat")
			.moveToParent() // N_PIPE
			.moveToLeft(N_SUBSHELL)
			.moveToLeft(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_PIPE
			.moveToRight(N_COMMAND).addArgument("tr").addArgument("a-z").addArgument("A-Z")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();

	ASSERT_EQ(output, "HELLO\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// ((echo hello && echo world) | tr a-z A-Z) | cat
TEST_F(TestExecuteAST, subshell_and_pipe_inside) {
	auto *ast = ASTBuilder(N_PIPE)
			.moveToRight(N_COMMAND).addArgument("cat")
			.moveToParent() // N_PIPE
			.moveToLeft(N_SUBSHELL)
			.moveToLeft(N_PIPE)
			.moveToRight(N_COMMAND).addArgument("tr").addArgument("a-z").addArgument("A-Z")
			.moveToParent() // N_PIPE
			.moveToLeft(N_SUBSHELL)
			.moveToLeft(N_AND)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_AND
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "HELLO\nWORLD\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// (exit 42)
TEST_F(TestExecuteAST, subshell_exit) {
	auto *ast = ASTBuilder(N_SUBSHELL)
			.moveToLeft(N_COMMAND).addArgument("exit").addArgument("42")
			.getAST();

	execute_ast(&ctx, ast);
	ASSERT_EQ(ctx.last_exit_status, 42);
}

// echo hello; echo world
TEST_F(TestExecuteAST, semicolon) {
	auto *ast = ASTBuilder(N_SEMICOLON)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_SEMICOLON
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "hello\nworld\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// echo 1; echo 2; echo 3
TEST_F(TestExecuteAST, semicolon_chain) {
	auto *ast = ASTBuilder(N_SEMICOLON)
			.moveToLeft(N_SEMICOLON)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("1")
			.moveToParent() // N_SEMICOLON
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("2")
			.moveToRoot() // N_SEMICOLON (root)
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("3")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "1\n2\n3\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// and, semicolon
// echo hello && echo world; echo ok
TEST_F(TestExecuteAST, and_semicolon) {
	auto *ast = ASTBuilder(N_SEMICOLON)
			.moveToLeft(N_AND)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_AND
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.moveToRoot()
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("ok")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "hello\nworld\nok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// pipe, semicolon
// echo hello | cat; echo ok
TEST_F(TestExecuteAST, pipe_semicolon) {
	auto *ast = ASTBuilder(N_SEMICOLON)
			.moveToLeft(N_PIPE)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_PIPE
			.moveToRight(N_COMMAND).addArgument("cat")
			.moveToRoot() // N_SEMICOLON
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("ok")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "hello\nok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// subshell, semicolon
// (echo hello && echo world); echo ok
TEST_F(TestExecuteAST, subshell_semicolon) {
	auto *ast = ASTBuilder(N_SEMICOLON)
			.moveToLeft(N_SUBSHELL)
			.moveToLeft(N_AND)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_AND
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.moveToRoot() // N_SEMICOLON
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("ok")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "hello\nworld\nok\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// semicolon in subshell
// (echo hello; echo world)
TEST_F(TestExecuteAST, semicolon_in_subshell) {
	auto *ast = ASTBuilder(N_SUBSHELL)
			.moveToLeft(N_SEMICOLON)
			.moveToLeft(N_COMMAND).addArgument("echo").addArgument("hello")
			.moveToParent() // N_SEMICOLON
			.moveToRight(N_COMMAND).addArgument("echo").addArgument("world")
			.getAST();

	testing::internal::CaptureStdout();
	execute_ast(&ctx, ast);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "hello\nworld\n");
	ASSERT_EQ(ctx.last_exit_status, 0);
}

// TODO: other built-in commands
// TODO: redirect
// TODO: check error message
