#include "minishell.h"

t_commands	*cmd_lst_new(void)
{
	t_commands	*element;

	element = malloc(sizeof(t_commands));
	if (element)
	{
		element->builtin = 0;
		element->cmd = NULL;
		element->next = NULL;
		return (element);
	}
	return (0);
}
