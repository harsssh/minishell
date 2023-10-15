#include <gtest/gtest.h>
extern "C" {
#include "libft.h"
}

TEST(basename, normal)
{
	char	*result;

	result = ft_basename("/path/to/file");
	EXPECT_STREQ(result, "file");
	free(result);
}

// with trailing slash
TEST(basename, trailing_slash)
{
	char	*result;

	result = ft_basename("/path/to/file//");
	EXPECT_STREQ(result, "file");
	free(result);
}

// file name
TEST(basename, file_name)
{
	char	*result;

	result = ft_basename("file");
	EXPECT_STREQ(result, "file");
	free(result);
}

// slash
TEST(basename, slash)
{
	char	*result;

	result = ft_basename("/");
	EXPECT_STREQ(result, "/");
	free(result);
}

// many slash
TEST(basename, many_slash)
{
	char	*result;

	result = ft_basename("///");
	EXPECT_STREQ(result, "/");
	free(result);
}

// dot
TEST(basename, dot)
{
	char	*result;

	result = ft_basename(".");
	EXPECT_STREQ(result, ".");
	free(result);
}

// dot-dot
TEST(basename, dot_dot)
{
	char	*result;

	result = ft_basename("..");
	EXPECT_STREQ(result, "..");
	free(result);
}

// NULL
TEST(basename, null)
{
	char	*result;

	result = ft_basename(nullptr);
	EXPECT_EQ(result, nullptr);
}

// empty
TEST(basename, empty)
{
	char	*result;

	result = ft_basename("");
	EXPECT_STREQ(result, ".");
	free(result);
}