#include "variables.h"
#include "libft.h"
#include "variables_internal.h"
#include <stdlib.h>

t_variable	*variable_create(char *name, char *value)
{
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	var->envstr = make_envstr(name, value);
	if (var->envstr == NULL)
	{
		free(var);
		return (NULL);
	}
	var->attributes = 0;
	return (var);
}

void        *variable_copy(void *data)
{
    t_variable *var;
    t_variable *new;

    var = (t_variable *)data;
    new = variable_create(ft_strdup(var->name), ft_strdup(var->value));
    if (new == NULL || new->name == NULL || new->value == NULL)
        return (NULL);
    new->envstr = ft_strdup(var->envstr);
    if (new->envstr == NULL)
    {
        variable_destroy(new);
        return (NULL);
    }
    new->attributes = var->attributes;
    return ((void *)new);
}
