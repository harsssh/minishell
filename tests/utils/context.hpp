#include <vector>
#include <utility>

using namespace std;

extern "C" {
#include "context.h"
}

class Context {
	t_context ctx{};

	public:
		Context();
		Context(const char *cwd);
		Context(initializer_list<pair<const char *, const char *>> vars);
		Context(const char *cwd, initializer_list<pair<const char *, const char *>> vars);
		explicit Context(int exit_status);
		t_context *getCtx();
};
