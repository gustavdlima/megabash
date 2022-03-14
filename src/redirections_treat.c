#include "minishell.h"

void	find_redirections(t_root *root)
{
	int	cmd_size;
	int	i;

	i= 0;
	while (root->input[i])
	{
		if (root->input[i] == '<')
		{
			printf("redirect_input(root)\n");
			return ;
		}
		if (root->input[i] == '>')
		{
			printf("redirect_output(root)\n");
			return ;
		}
		i++;
	}
	i = 0;
	cmd_size = ft_strlen(root->input);
	root->command = matrix_split(root->input, cmd_size);
	while (root->command[i])
	{
		root->command[i] = metacharacters_treat(root->command[i]);
		root->command[i] = no_quotes(root->command[i]);
		printf("%s\n", root->command[i]);
		i++;
	}
}
