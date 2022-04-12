#include "minishell.h"

void	export(char **command)
{
	int	i;
	char	*name;
	char	*content;
	t_env	*node;

	node = g_megabash.env;
	i = 1;
	while (command[i])
	{
		name = get_env_name(g_megabash.cmd_list->content[i]);
		content = get_env_path(g_megabash.cmd_list->content[i]);
		node = get_env_node(g_megabash.env, name);
		if (!node)
		{
			printf("ANTES ENV_ADDBACK\n");
			env_addback(&g_megabash.env, env_lst_new(name, content));
			printf("DEPOIS ENV_ADDBACK\n");
		}
		else
		{
			env_content_to_null(node, name);
			node->content = ft_strdup(content);
		}
		i++;
	}
}
