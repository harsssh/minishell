#include <gtest/gtest.h>
extern "C" {
#include "builtins.h"
#include "variables.h"
#include "ft_list.h"
}

TEST(builtins_unset, normal)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME1", "VALUE1", 1);
	setvar(&ctx, "NAME2", "VALUE2", 1);

	char *args[] = {(char *)"NAME1", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME1"), nullptr);
	EXPECT_NE(getvar(&ctx, "NAME2"), nullptr);
}

// 複数引数
TEST(builtins_unset, normal2)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME1", "VALUE1", 1);
	setvar(&ctx, "NAME2", "VALUE2", 1);

	char *args[] = {(char *)"NAME1", (char *)"NAME2", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME1"), nullptr);
	EXPECT_EQ(getvar(&ctx, "NAME2"), nullptr);
}

// オプションは無視する
TEST(builtins_unset, ignore_option)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"-a", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// 複数のオプション
TEST(builtins_unset, multiple_option)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"-ab", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// 複数のオプション2
TEST(builtins_unset, multiple_option2)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"-a", (char *)"-b", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// "--" を含む
TEST(builtins_unset, include_end_of_options)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"-a", (char *)"--", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// "-" を含む
TEST(builtins_unset, include_end_of_options2)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"-a", (char *)"-", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// 最初が "--"
TEST(builtins_unset, start_with_end_of_options)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME", "VALUE", 1);

	char *args[] = {(char *)"--", (char *)"NAME", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME"), nullptr);
}

// unsetvar が失敗する場合も継続
TEST(builtins_unset, continue_on_unsetvar_error)
{
	t_context ctx;
	ctx.variables = ft_list_create();

	setvar(&ctx, "NAME1", "VALUE1", 1);
	setvar(&ctx, "NAME2", "VALUE2", 1);

	char *args[] = {(char *)"NAME1", (char *)"INVALID=NAME",(char *)"NAME2", nullptr};
	builtins_unset(&ctx, args);

	EXPECT_EQ(getvar(&ctx, "NAME1"), nullptr);
	EXPECT_EQ(getvar(&ctx, "NAME2"), nullptr);
}
