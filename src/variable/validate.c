#include "variable.h"
#include "libft.h"

static int is_valid_character(int c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_valid_identifier(const char *identifier)
{
	if (!(ft_isalpha(*identifier) || *identifier == '_'))
		return (0);
	return (ft_strall(identifier + 1, is_valid_character));
}
