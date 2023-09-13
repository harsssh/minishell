#include "variables.h"
#include "variables_internal.h"
#include <stdlib.h>

static bool is_inheritable(void *data)
{
    t_variable *var;

    var = (t_variable *)data;
    return ((var->attributes & VAR_ATTR_EXPORTED) 
        && !(var->attributes & VAR_ATTR_NO_VALUE));
}

static char **to_environ_array(t_list *vars)
{
    char        **array;
    char        **cur;
    t_node      *node;
    size_t      len;

    len = vars->size;
    array = (char **)malloc(sizeof(char *) * (len + 1));
    if (array == NULL)
        return (NULL);
    cur = array;
    node = vars->head;
    while (len--)
    {
        *cur = ((t_variable *)node->data)->envstr;
        ((t_variable *)node->data)->envstr = NULL;
        ++cur;
        node = node->next;
    }
    *cur = NULL;
    return (array);
}

char    **get_environ(t_context *ctx)
{
    t_list *filtered;
    char    **envp;

    filtered = ft_list_filter(ctx->variables, is_inheritable, variable_copy, variable_destroy);
    envp = to_environ_array(filtered);
    ft_list_destroy(filtered, variable_destroy);
    return (envp);
}