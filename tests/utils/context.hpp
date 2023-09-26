#include <vector>
#include <utility>

using namespace std;

extern "C" {
#include "context.h"
}

class Context {
	t_context ctx;

	public:
		Context();
		Context(vector<pair<const char *, const char *>> vars);
		t_context *getCtx();
};
