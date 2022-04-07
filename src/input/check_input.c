#include "minishell.h"

void check_input(void)
{
	t_token	*list_temp;

	list_temp = g_megabash.token_list;
	print_token(list_temp);
	while (list_temp)
	{
		printf("oi?\n");
		if (is_builtin(list_temp->content))
			printf("BUILTIN -> %s\n", list_temp->content);
		else if (is_operator(list_temp->content))
			printf("OPERATOR -> %s\n", list_temp->content);
		else if (what_cmd(list_temp->content))
			printf("COMMAND -> %s\n", list_temp->content);
		else
			printf("ARGUMENT OR FLAG-> %s\n", list_temp->content);
		if (list_temp->next)
		list_temp = list_temp->next;
	}
}
