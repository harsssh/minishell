#include <gtest/gtest.h>

extern "C" {
#include "builtin.h"
#include "variable.h"
}

TEST(builtin_env, normal) {
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "NAME1", "VALUE1", 1);
	setvar(&ctx, "NAME2", "VALUE2", 1);
	// exportする
	ft_list_iter(ctx.variables, [](void *data) {
		auto *var = (t_variable *) data;
		var->attributes |= VAR_ATTR_EXPORTED;
	});
	// NAME3はexportされていない
	setvar(&ctx, "NAME3", "VALUE3", 1);

	testing::internal::CaptureStdout();
	char *args[] = {nullptr};
	builtin_env(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), "NAME1=VALUE1\nNAME2=VALUE2\n");
}

// 環境変数なし
TEST(builtin_env, no_env) {
	t_context ctx;

	ctx.variables = ft_list_create();

	testing::internal::CaptureStdout();
	char *args[] = {nullptr};
	builtin_env(&ctx, args);
	auto output = testing::internal::GetCapturedStdout();
	ASSERT_STREQ(output.c_str(), "");
}