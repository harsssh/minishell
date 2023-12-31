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

Context::Context(const char *cwd) {
	*this = Context();
	ctx.cwd = (char *)cwd;
}

Context::Context(initializer_list<pair<const char *, const char *>> vars) {
	*this = Context();
	for (auto [name, value] : vars) {
		t_variable *var = variable_create(name, value);
		ft_list_push_back(ctx.variables, var);
	}
}

Context::Context(const char *cwd, initializer_list<pair<const char *, const char *>> vars)
{
	*this = Context(vars);
	ctx.cwd = (char *)cwd;
}

Context::Context(int exit_status) {
	*this = Context();
	ctx.last_exit_status = exit_status;
}

t_context *Context::getCtx() {
	return &ctx;
}
