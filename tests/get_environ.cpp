#include <gtest/gtest.h>
extern "C"
{
#include "variables.h"
#include "variables_internal.h"
}

class TestGetEnviron : public ::testing::Test
{
protected:
    t_context ctx = {.shell_name = "minishell"};

    void SetUp() override
    {
        ctx.variables = ft_list_create();
        // exported, has value
        setvar(&ctx, "VAR1", "value1", 1);
        // exported, no value
        setvar(&ctx, "VAR2", "value2", 1);
        // not exported, has value
        setvar(&ctx, "VAR3", "value3", 1);
        // exported, has value (same as VAR1)
        setvar(&ctx, "VAR4", "value4", 1);

        auto var = getvar(&ctx, "VAR1");
        var->attributes |= VAR_ATTR_EXPORTED;

        var = getvar(&ctx, "VAR2");
        var->attributes |= VAR_ATTR_EXPORTED | VAR_ATTR_NO_VALUE;

        var = getvar(&ctx, "VAR4");
        var->attributes |= VAR_ATTR_EXPORTED;
    }

    void TearDown() override
    {
        ft_list_destroy(ctx.variables, variable_destroy);
    }
};

TEST_F(TestGetEnviron, normal) {
    char **envp = get_environ(&ctx);
    EXPECT_STREQ(envp[0], "VAR1=value1");
    EXPECT_STREQ(envp[1], "VAR4=value4");
    EXPECT_EQ(envp[2], nullptr);
}