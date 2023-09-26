#include "context.hpp"

extern "C" {
#include "libft.h"
#include "variables_internal.h"
}

Context::Context() {
	ctx.shell_name = "test_shell";
	ctx.variables = ft_list_create();
	ctx.cwd = "/tmp";
	ctx.last_exit_status = 0;
}

Context::Context(vector<pair<const char *, const char *>> vars) {
	*this = Context();
	for (auto [name, value] : vars) {
		t_variable *var = variable_create(name, value);
		ft_list_push_back(ctx.variables, var);
	}
}

t_context *Context::getCtx() {
	return &ctx;
}
