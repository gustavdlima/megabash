#include "minishell.h"

void	export(char *command)
{
	int	i;
	char	*name;
	char	*content;
	t_env	*node;

	i = 1;
	while (command[i])
	{
		name = get_env_name(root->command[i]);
		content = get_env_path(root->command[i]);
		node = get_env_node(env, name, ft_strlen(name));
		if (node == NULL)
		{
			env_addback(&node, env_lstnew(name, content));
		}
		else
		{
			env_content_to_null(node, name);
			node->content = content;
		}
		i++;
		// print_env(env);
		// printf("Name: %s\n", name);
		// printf("Content: %s\n", content);
		// free(name);
		// free(content);
	}
}
