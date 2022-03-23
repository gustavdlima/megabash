#include "minishell.h"

int	find_pipe(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// void	pipe_treat(t_root *root, t_env *env)
// {
// 	t_root	*pipe_cmd;

// 	pipe_cmd->command = ft_split(root, '|');
// 	for (int i = 0; pipe_cmd->command[i]; i++)
// 	{
// 		printf("pipe_cmd->command[%d] : %s\n", i, pipe_cmd->command[i]);
// 	}
// 	for (int i = 0; pipe_cmd->command[i]; i++)
// 	{
// 		pipe_cmd->command[i] = input_treat(pipe_cmd->command[i], env);
// 	}

// 	// (void)env;
// 	// input_treat(root, env);
// }
