#include <vector>
#include <gtest/gtest.h>

using namespace std;

extern "C" {
#include "libft.h"
#include "token.h"
}

#define ANY_ORDER false

bool compareTokenStream(t_list *got, vector<pair<t_token_type, const char *>> expect);
::testing::AssertionResult compareStrList(t_list *got, vector<const char *> expect);
::testing::AssertionResult compareStrList(t_list *got, vector<const char *> expect, bool strictOrder);
