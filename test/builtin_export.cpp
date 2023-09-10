#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>

extern "C" {
#include "builtin.h"
#include "variable.h"
#include "variable_internal.h"
}

class TestBuiltinExport : public ::testing::Test {
protected:
	t_context ctx = {.shell_name = "minishell"};
	const std::string DECLARED_NAME = "declare -x NAME=\"name\"\n";
	const std::string DECLARED_EXPORTED = "declare -x EXPORTED=\"exported\"\n";
	const std::string DECLARED_EXPORTED_NO_VALUE = "declare -x EXPORTED_NO_VALUE\n";

	void SetUp() override {
		ctx.variables = ft_list_create();

		// 変数の初期化
		setvar(&ctx, "NAME", "name", 1);
		setvar(&ctx, "EXPORTED", "exported", 1);
		setvar(&ctx, "EXPORTED_NO_VALUE", "exported_no_value", 1);
		// attributeを設定
		auto var = getvar(&ctx, "EXPORTED");
		var->attributes |= VAR_ATTR_EXPORTED;
		var = getvar(&ctx, "EXPORTED_NO_VALUE");
		var->attributes |= VAR_ATTR_EXPORTED | VAR_ATTR_NO_VALUE;
	}

	void TearDown() override {
		ft_list_destroy(ctx.variables, variable_destroy);
	}

	int run_export(char *s) {
		char *argv[2] = {nullptr};
		if (s == nullptr)
			return builtin_export(&ctx, argv);
		argv[0] = s;
		return builtin_export(&ctx, argv);
	}
};

// 引数無しで, 環境変数を全て表示する
TEST_F(TestBuiltinExport, NoArgs) {
	testing::internal::CaptureStdout();
	auto status = run_export(nullptr);

	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE
	);
}

// export EXPORTED_NO_VALUE
// 値未定義の環境変数をexport, 変化なし
TEST_F(TestBuiltinExport, ExportNoValue) {
	auto status = run_export("EXPORTED_NO_VALUE");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "EXPORTED_NO_VALUE");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_TRUE(var->attributes & VAR_ATTR_NO_VALUE);
}

// export NAME
// シェル変数をexport
TEST_F(TestBuiltinExport, ExportName) {
	// capture
	testing::internal::CaptureStdout();
	auto status = run_export("NAME");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "NAME");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_NAME +
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE
	);
}

// EXPORTED_NO_VALUE=new_value, 引数なしexport
// 値未定義の環境変数に値をセット
TEST_F(TestBuiltinExport, ExportNoValueAfterSetvar) {
	// capture
	testing::internal::CaptureStdout();
	setvar(&ctx, "EXPORTED_NO_VALUE", "new_value", 1);

	auto status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_EXPORTED +
			  "declare -x EXPORTED_NO_VALUE=\"new_value\"\n"
	);
}

// export NEW_VAR
TEST_F(TestBuiltinExport, ExportNewVar) {
	auto status = run_export("NEW_VAR");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "NEW_VAR");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_TRUE(var->attributes & VAR_ATTR_NO_VALUE);
}

// export NEW_VAR=value
TEST_F(TestBuiltinExport, ExportNewVarWithValue) {
	// capture
	testing::internal::CaptureStdout();
	auto status = run_export("NEW_VAR=value");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "NEW_VAR");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_FALSE(var->attributes & VAR_ATTR_NO_VALUE);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE +
			  "declare -x NEW_VAR=\"value\"\n"
	);
}

// export NEW_VAR+=value
TEST_F(TestBuiltinExport, ExportNewVarPlusEqualWithValue) {
	// capture
	testing::internal::CaptureStdout();
	auto status = run_export("NEW_VAR+=value");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "NEW_VAR");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_FALSE(var->attributes & VAR_ATTR_NO_VALUE);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE +
			  "declare -x NEW_VAR=\"value\"\n"
	);
}

// export NAME=value
TEST_F(TestBuiltinExport, ExportNameWithValue) {
	// capture
	testing::internal::CaptureStdout();
	auto status = run_export("NAME=value");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "NAME");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_FALSE(var->attributes & VAR_ATTR_NO_VALUE);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  "declare -x NAME=\"value\"\n" +
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE
	);
}

// export EXPORTED+=value
TEST_F(TestBuiltinExport, ExportPlusEqualWithValue) {
	// capture
	testing::internal::CaptureStdout();
	auto status = run_export("EXPORTED+=value");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "EXPORTED");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_FALSE(var->attributes & VAR_ATTR_NO_VALUE);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  "declare -x EXPORTED=\"exportedvalue\"\n" +
			  DECLARED_EXPORTED_NO_VALUE
	);
}

// export =value
TEST_F(TestBuiltinExport, ExportEqualWithValue) {
	// capture
	testing::internal::CaptureStderr();
	auto status = run_export("=value");
	EXPECT_EQ(status, EXIT_FAILURE);
	EXPECT_EQ(testing::internal::GetCapturedStderr(),
			  "minishell: export: `=value': not a valid identifier\n");
}

// export +=value
TEST_F(TestBuiltinExport, ExportBeginPlusEqualWithValue) {
	// capture
	testing::internal::CaptureStderr();
	auto status = run_export("+=value");
	EXPECT_EQ(status, EXIT_FAILURE);
	EXPECT_EQ(testing::internal::GetCapturedStderr(),
			  "minishell: export: `+=value': not a valid identifier\n");
}

// export 0INVALID=value
TEST_F(TestBuiltinExport, ExportInvalidEqualWithValue) {
	testing::internal::CaptureStderr();
	auto status = run_export("0INVALID=value");
	EXPECT_EQ(status, EXIT_FAILURE);
	EXPECT_EQ(testing::internal::GetCapturedStderr(),
			  "minishell: export: `0INVALID=value': not a valid identifier\n");
}

// export ' NAME '=value
TEST_F(TestBuiltinExport, ExportSpaceNameEqualWithValue) {
	testing::internal::CaptureStderr();
	auto status = run_export(" NAME =value");
	EXPECT_EQ(status, EXIT_FAILURE);
	EXPECT_EQ(testing::internal::GetCapturedStderr(),
			  "minishell: export: ` NAME =value': not a valid identifier\n");
}

// export _=value
// 無視される
TEST_F(TestBuiltinExport, ExportUnderScoreEqualWithValue) {
	testing::internal::CaptureStdout();
	auto status = run_export("_=value");
	EXPECT_EQ(status, EXIT_SUCCESS);
	// attributeを確認
	auto var = getvar(&ctx, "_");
	EXPECT_EQ(var, nullptr);

	status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  DECLARED_EXPORTED +
			  DECLARED_EXPORTED_NO_VALUE
	);
}

// unsetして引数なしexport
TEST_F(TestBuiltinExport, ExportAfterUnset) {
	// capture
	testing::internal::CaptureStdout();
	unsetvar(&ctx, "EXPORTED_NO_VALUE");
	auto status = run_export(nullptr);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(), DECLARED_EXPORTED);
}

// 複数の変数をexport
TEST(TestBuiltinExportMultiple, ExportMultiple) {
	testing::internal::CaptureStderr();
	testing::internal::CaptureStdout();
	t_context ctx = {
			.shell_name = "minishell",
			.variables = ft_list_create(),
	};
	char *argv[] = {"VAR1=value", "=value", "VAR2", "0=1", nullptr};
	auto status = builtin_export(&ctx, argv);

	EXPECT_EQ(status, EXIT_FAILURE);
	// attributeを確認
	auto var = getvar(&ctx, "VAR1");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_FALSE(var->attributes & VAR_ATTR_NO_VALUE);
	var = getvar(&ctx, "VAR2");
	EXPECT_TRUE(var->attributes & VAR_ATTR_EXPORTED);
	EXPECT_TRUE(var->attributes & VAR_ATTR_NO_VALUE);
	var = getvar(&ctx, "0");
	EXPECT_EQ(var, nullptr);
	// エラーを確認
	EXPECT_EQ(testing::internal::GetCapturedStderr(),
			  "minishell: export: `=value': not a valid identifier\n"
			  "minishell: export: `0=1': not a valid identifier\n");

	// exportを確認
	argv[0] = nullptr;
	status = builtin_export(&ctx, argv);
	EXPECT_EQ(status, EXIT_SUCCESS);
	EXPECT_EQ(testing::internal::GetCapturedStdout(),
			  "declare -x VAR1=\"value\"\n"
			  "declare -x VAR2\n"
	);
}