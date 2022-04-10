#include "minishell.h"

void check_input(void)
{
	t_token	*list_temp;

	list_temp = g_megabash.token_list;
	while (list_temp)
	{
		if (is_builtin(list_temp->content))
			g_megabash.token_list->type = IS_BUILTIN;
		else if (is_operator(list_temp->content))
			g_megabash.token_list->type = IS_PIPE; // MUDAR DEPOIS
		else if (what_cmd(list_temp->content))
			g_megabash.token_list->type = IS_CMD;
		// else
		// 	// printf("ARGUMENT OR FLAG-> %s\n", list_temp->content);
		list_temp = list_temp->next;
	}
}
