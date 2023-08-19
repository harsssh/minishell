#include "builtin_internal.h"

char	**ignore_options(char **args)
{
	int	c;

	init_get_next_option();
	while (*args)
	{
		c = get_next_option(*args, "");
		if (c == END_OF_OPTIONS)
			break ;
		if (c == END_OF_ARG)
			++args;
	}
	return (args);
}