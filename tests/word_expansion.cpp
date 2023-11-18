#include <filesystem>
#include <gtest/gtest.h>
#include "utils/context.hpp"
#include "utils/compare_list.hpp"

extern "C" {
#include "word_expansion/word_expansion_internal.h"
#include "context.h"
#include "expansion.h"
#include <fcntl.h>
}

class ExpandFilenameTest : public testing::Test {
protected:
	std::vector<std::string> filenames = {".minish", "a.minish", "b.minish", "minishell", "a.txt", "a.minishe", "'.quote", "\".quote"};
	const char *test_files_dir = "/tmp/minishell/";
	char *old_cwd = getcwd(nullptr, 0);

	void SetUp() override {
		mkdir(test_files_dir, 0777);
		chdir(test_files_dir);
		for (auto &filename: filenames) {
			creat(filename.c_str(), 0777);
		}
	}

	void TearDown() override {
		for (auto &filename: filenames) {
			std::remove(filename.c_str());
		}
		rmdir(test_files_dir);
		chdir(old_cwd);
	}
};

TEST(expand_parameters, normal) {
	auto input = "'hello '$USER' 42'";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'hello 'root' 42'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, no_param) {
	auto input = "'hello world'";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'hello world'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, expand_in_double_quotes) {
	auto input = "\"hello $USER 42\"";
	auto ctx = Context({{"USER", "root"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\"hello root 42\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, multiple) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"},
						{"b", "2"},
						{"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"123"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"},
						{"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"13"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined2) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "1"},
						{"b", "2"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"12"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined3) {
	auto input = "$a$b$c";
	auto ctx = Context({{"b", "2"},
						{"c", "3"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"23"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, undefined4) {
	auto input = "$a$b$c";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, empty) {
	auto input = "";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, empty2) {
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, single_quote) {
	auto input = "'$a'";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'$a'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, single_double) {
	auto input = "'\"$a\"'";
	auto ctx = Context({}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"'\"$a\"'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, double_single) {
	auto input = "\"'$a'\"";
	auto ctx = Context({{"a", "1"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\"'1'\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, expanded_single_quote) {
	auto input = "$a";
	auto ctx = Context({{"a", "'1'"}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\\'1\\'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, expanded_mixed_quotes) {
	auto input = "$a";
	auto ctx = Context({{"a", "\"'1'\""}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\\\"\\'1\\'\\\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_parameters, expanded_double_quote) {
	auto input = "$a";
	auto ctx = Context({{"a", "\"1\""}}).getCtx();
	auto result = expand_parameters(input, ctx);
	auto expected = {"\\\"1\\\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, normal) {
	auto input = "$a";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	auto expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, multiple) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "},
						{"b", "  world  "},
						{"c", "  42  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	auto expected = {"hello", "world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, empty) {
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, empty2) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""},
						{"b", ""},
						{"c", ""}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, mixed_empty) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"b", "  "},
						{"c", "world"}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, double_quote) {
	auto input = "\"$a\"";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {"\"  hello  world  \""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, expanded_quote) {
	auto input = "$a";
	auto ctx = Context({{"a", "'hello  world'"}}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {"\\'hello", "world\\'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(split_word, single_quote_with_variable) {
	auto input = "'$a'";
	auto ctx = Context({}).getCtx();
	auto result = split_word(expand_parameters(input, ctx));
	vector<const char *> expected = {"'$a'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, forward) {
	auto input = "*.minish";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"a.minish", "b.minish"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

TEST_F(ExpandFilenameTest, backward) {
	auto input = ".mini*";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {".minish"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, middle) {
	auto input = "*minishe*";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"a.minishe", "minishell"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

TEST_F(ExpandFilenameTest, no_expansion) {
	auto input = "*.no";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"*.no"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, no_expansion2) {
	auto input = "*.minishell";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"*.minishell"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote) {
	auto input = "'*.minish'";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"'*.minish'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote2) {
	auto input = "\"*.minish\"";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"\"*.minish\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote3) {
	auto input = "*'.minish'";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"a.minish", "b.minish"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

TEST_F(ExpandFilenameTest, quote4) {
	auto input = "*\".minish\"";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"a.minish", "b.minish"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

TEST_F(ExpandFilenameTest, quote5) {
	auto input = ".mini*";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {".minish"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote6) {
	auto input = "\"\"*";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"a.minish", "b.minish", "minishell", "a.txt", "a.minishe", "\\'.quote", "\\\".quote"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

// use `expand_word` to remove quotes
TEST_F(ExpandFilenameTest, quote_no_match) {
	auto input = "\"*\"";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"*"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote_no_match2) {
	auto input = "x\"*\"x";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"x*x"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST_F(ExpandFilenameTest, quote_in_file) {
	auto input = "*.quote";
	auto *ctx = Context("/tmp/minishell").getCtx();
	auto result = expand_filenames(split_word(expand_parameters(input, ctx)));
	auto expected = {"\\'.quote", "\\\".quote"};

	ASSERT_TRUE(compareStrList(result, expected, ANY_ORDER));
}

TEST(expand_word, normal) {
	auto input = "$a";
	auto ctx = Context({{"a", "hello"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, multiple) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"b", "world"},
						{"c", "42"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"helloworld42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, empty) {
	auto input = "$a";
	auto ctx = Context({{"a", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, empty2) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""},
						{"b", ""},
						{"c", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, mixed_empty) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"b", ""},
						{"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined) {
	auto input = "$a";
	auto ctx = Context({{"b", "hello"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined2) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined3) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"b", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined4) {
	auto input = "$a$b$c";
	auto ctx = Context({{"b", "hello"},
						{"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined5) {
	auto input = "$a$b$c";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined6) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", ""},
						{"b", ""},
						{"c", ""}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, undefined7) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "hello"},
						{"b", ""},
						{"c", "world"}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"helloworld"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space) {
	auto input = "$a";
	auto ctx = Context({{"a", "  hello  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space2) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "},
						{"b", "  world  "},
						{"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello", "world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space3) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "},
						{"b", "  "},
						{"c", "  world  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello", "world"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space4) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  "},
						{"b", "  world  "},
						{"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"world", "42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space5) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  hello  "},
						{"b", "  "},
						{"c", "  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"hello"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, space6) {
	auto input = "$a$b$c";
	auto ctx = Context({{"a", "  "},
						{"b", "  "},
						{"c", "  42  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, single_quote) {
	auto input = "'$a'";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"$a"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, double_quote) {
	auto input = "\"$a\"";
	auto ctx = Context({{"a", "  hello  world  "}}).getCtx();
	auto result = expand_word(input, ctx);
	vector<const char *> expected = {"  hello  world  "};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, single_double) {
	auto input = "'\"$a\"'";
	auto ctx = Context({}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"\"$a\""};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, double_single) {
	auto input = "\"'$a'\"";
	auto ctx = Context({{"a", "1"}}).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"'1'"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, exit_status) {
	auto input = "$?";
	auto ctx = Context(42).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"42"};

	ASSERT_TRUE(compareStrList(result, expected));
}

TEST(expand_word, exit_status_many) {
	auto input = "$?$?$?";
	auto ctx = Context(42).getCtx();
	auto result = expand_word(input, ctx);
	auto expected = {"424242"};

	ASSERT_TRUE(compareStrList(result, expected));
}
