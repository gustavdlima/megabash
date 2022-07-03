#include "minishell.h"

void	free_megabash(void)
{
	free_env(g_megabash.env);
	free_commands(g_megabash.cmd_list);
	rl_clear_history();
}

void	free_cmd_megabash(void)
{
	free_commands(g_megabash.cmd_list);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
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
	free(env);
}
