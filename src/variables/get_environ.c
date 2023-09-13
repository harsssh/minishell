#include "variables.h"

static bool is_inheritable(void *data)
{
    t_variable *var;

    var = (t_variable *)data;
    return ((var->attributes & VAR_ATTR_EXPORTED) 
        && !(var->attributes & VAR_ATTR_NO_VALUE));
}

char    **get_environ(t_context *ctx)
{
    t_list *filtered;

    filtered = ft_list_filter(ctx->variables, is_inheritable, )
}