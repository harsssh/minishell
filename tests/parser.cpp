#include <gtest/gtest.h>
extern "C" {
#include "parser_internal.h"
#include "parser.h"
}

TEST(parser, normal)
{
	char *input = "ls";
	auto result = parse(input);
}
