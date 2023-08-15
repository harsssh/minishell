#include <gtest/gtest.h>
extern "C" {
#include "variable.h"
#include "variable_internal.h"
#include "ft_list.h"
}

// getvar
TEST(getvar, normal) {
	t_context ctx;

	ctx.variables = ft_list_create();
	t_variable *var1 = variable_create("name1", "value1");
	ft_list_push_back(ctx.variables, var1);
	t_variable *var2 = variable_create("name2", "value2");
	ft_list_push_back(ctx.variables, var2);

	ASSERT_TRUE(getvar(&ctx, "name1") == var1);
	ASSERT_TRUE(getvar(&ctx, "name2") == var2);
	ASSERT_TRUE(getvar(&ctx, "not_found") == nullptr);
}

// setvar
TEST(setvar, normal)
{
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "name1", "value1", 1);
	setvar(&ctx, "name2", "value2", 1);
	ASSERT_TRUE(ctx.variables->size == 2);

	t_variable *var1 = getvar(&ctx, "name1");
	ASSERT_TRUE(var1 != nullptr);
	EXPECT_STREQ(var1->name, "name1");
	EXPECT_STREQ(var1->value, "value1");
	EXPECT_STREQ(var1->envstr, "name1=value1");
	EXPECT_EQ(var1->attributes, 0);

	t_variable *var2 = getvar(&ctx, "name2");
	ASSERT_TRUE(var2 != nullptr);
	EXPECT_STREQ(var2->name, "name2");
	EXPECT_STREQ(var2->value, "value2");
	EXPECT_STREQ(var2->envstr, "name2=value2");
	EXPECT_EQ(var2->attributes, 0);
}

// overwrite=0で既存の変数を上書きしない
TEST(setvar, overwrite0)
{
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "name1", "value1", 0);
	setvar(&ctx, "name1", "value2", 0);
	ASSERT_TRUE(ctx.variables->size == 1);

	t_variable *var1 = getvar(&ctx, "name1");
	ASSERT_TRUE(var1 != nullptr);
	EXPECT_STREQ(var1->name, "name1");
	EXPECT_STREQ(var1->value, "value1");
	EXPECT_STREQ(var1->envstr, "name1=value1");
	EXPECT_EQ(var1->attributes, 0);
}

// overwrite=1で既存の変数を上書きする
TEST(setvar, overwrite1)
{
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "name1", "value1", 1);
	setvar(&ctx, "name1", "value2", 1);
	ASSERT_TRUE(ctx.variables->size == 1);

	t_variable *var1 = getvar(&ctx, "name1");
	ASSERT_TRUE(var1 != nullptr);
	EXPECT_STREQ(var1->name, "name1");
	EXPECT_STREQ(var1->value, "value2");
	EXPECT_STREQ(var1->envstr, "name1=value2");
	EXPECT_EQ(var1->attributes, 0);
}

// nameが不正 (NULL, 空文字, =を含む)
TEST(setvar, invalid_name)
{
	t_context ctx;

	ctx.variables = ft_list_create();

	int ret = setvar(&ctx, NULL, "value1", 1);
	ASSERT_TRUE(ret == -1);

	setvar(&ctx, "", "value1", 1);
	ASSERT_TRUE(ret == -1);

	setvar(&ctx, "name1=value1", "value1", 1);
	ASSERT_TRUE(ret == -1);

	ASSERT_TRUE(ctx.variables->size == 0);
}

// unsetvar
TEST(unsetvar, normal)
{
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "name1", "value1", 1);
	setvar(&ctx, "name2", "value2", 1);
	ASSERT_TRUE(ctx.variables->size == 2);

	unsetvar(&ctx, "name1");
	ASSERT_TRUE(ctx.variables->size == 1);
	ASSERT_TRUE(getvar(&ctx, "name1") == nullptr);
	ASSERT_TRUE(getvar(&ctx, "name2") != nullptr);

	unsetvar(&ctx, "name2");
	ASSERT_TRUE(ctx.variables->size == 0);
	ASSERT_TRUE(getvar(&ctx, "name1") == nullptr);
	ASSERT_TRUE(getvar(&ctx, "name2") == nullptr);
}

// unsetvar, nameが不正
TEST(unsetvar, invalid_name)
{
	t_context ctx;

	ctx.variables = ft_list_create();
	setvar(&ctx, "name1", "value1", 1);
	setvar(&ctx, "name2", "value2", 1);
	ASSERT_TRUE(ctx.variables->size == 2);

	unsetvar(&ctx, NULL);
	ASSERT_TRUE(ctx.variables->size == 2);

	unsetvar(&ctx, "");
	ASSERT_TRUE(ctx.variables->size == 2);

	unsetvar(&ctx, "name1=value1");
	ASSERT_TRUE(ctx.variables->size == 2);
}