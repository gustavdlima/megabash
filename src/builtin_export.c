#include "minishell.h"

void	export(t_root *root, t_env *env)
{
	int	i;
	char	*name;
	char	*content;
	t_env	*node;

	i = 1;
	while(root->command[i])
	{
		name = get_env_name(root->command[i]);
		content = get_env_path(root->command[i]);
		node = get_env_node(env, name, ft_strlen(name));
		if (node == NULL)
		{
			printf("name: %s\ncontent: %s\n", name, content);
			env_addback(&env, env_lstnew(name, content));
			t_env *temp = env_last_node(node);
			printf("TEMP: %s\n", temp->content);
			// printf("O NODE NAO EXISTE\n");
			printf("node == NULL: %s\n", node->content);
		}
		else
		{
			env_content_to_null(env, name);
			node->content = content;
		printf("ELSE node: %s\n", node->content);

		}
		i++;
		// print_env(env);
		// printf("Name: %s\n", name);
		// printf("Content: %s\n", content);
		// free(name);
		// free(content);
	}
	printf("node: %s\n", node->content);
}


// Tratar o argumento e separar em nome e conteudo

// basicamente cria uma variavel de ambiente e adiciona conteudo
// 1. a partir do root->command[1] vamos ter os argumentos do export
// 2. o que tiver antes de = vai ser o name e depois o conteudo
// 3. se a variavel ja exista mudo o conteudo, se nao crio e adiciono a lista
// 4. se nao tiver nada apos o =, coloco o conteudo em null
