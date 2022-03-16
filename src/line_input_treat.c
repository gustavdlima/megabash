#include "minishell.h"

void	input_treat(t_root *root, t_env *env)
{
	int	cmd_size;
	int	i;

	i = 0;
	cmd_size = ft_strlen(root->input);
	root->command = tokenizer(root->input, cmd_size);
	while (root->command[i])
	{
		root->command[i] = metacharacters_treat(root->command[i], env);
		root->command[i] = no_quotes(root->command[i]);
		printf("%s\n", root->command[i]);
		i++;
	}
}
