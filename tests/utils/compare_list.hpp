#include <vector>

using namespace std;

extern "C" {
#include "libft.h"
#include "token.h"
}

bool compareTokenStream(t_list *got, vector<pair<t_token_type, const char *>> expect);
bool compareStrList(t_list *got, vector<const char *> expect);
