#include "ft_list.h"
#include <stdlib.h>

char	**list_to_string_array(t_list *list, char *(*f)(void *data))
{
	char **array;
	char **cur;
	t_node *node;

	array = (char **)malloc(sizeof(char *) * (list->size + 1));
	if (array == NULL)
		return (NULL);
	cur = array;
	node = list->head;
	while (node != NULL)
	{
		*cur = f(node->data);
		++cur;
		node = node->next;
	}
	*cur = NULL;
	return (array);
}
