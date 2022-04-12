#include "minishell.h"

void	free_megabash(void)
{
	printf("exit\n");
	free_env(g_megabash.env);
	free_token(g_megabash.token_list);
	rl_clear_history();
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->content);
		free(temp);
	}
}
