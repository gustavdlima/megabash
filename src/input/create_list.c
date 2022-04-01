#include "minishell.h"

void create_list(char *input)
{
	char **content;

	content = ft_split(input, ' ');
	reverse_space(content);
	for (int i = 0; content[i]; i++)
		printf("content: %s\n", content[i]);
}

// splitar a linha de comando
// inicializar a lista
// como vou saber o momento correto do inicio e fim do comando? PIPE ou <><<>>
// como vai funcionar com casos de && e redirecionamento?


