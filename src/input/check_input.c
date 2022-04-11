#include "minishell.h"

void check_input(void)
{
	t_token	*list_temp;

	list_temp = g_megabash.token_list;
	while (list_temp)
	{
		if (is_builtin(list_temp->content))
			list_temp->type = IS_BUILTIN;
		else if (is_operator(list_temp->content))
			list_temp->type = is_operator(list_temp->content);
		else if (what_cmd(list_temp->content))
			list_temp->type = IS_CMD;
		else
			list_temp->type = IS_PARAMETER;
		list_temp = list_temp->next;
	}
}
