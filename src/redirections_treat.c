#include "minishell.h"

int	theres_delimiter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '<')
		{
			while (cmd[i] && cmd[i] != '<')
				i++;
			if (cmd[i] == '<')
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	find_redirections(void)
{
	int	i;

	i= 0;
	while (g_megabash.input[i])
	{
		if (g_megabash.input[i] == '<')
		{
			i++;
			if (g_megabash.input[i] == '<')
				printf("should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!\n");
			else
				printf("redirect_input(g_megabash)\n");
			return ;
		}
		if (g_megabash.input[i] == '>')
		{
			i++;
			if (g_megabash.input[i] == '>')
				printf("should redirect output in append mode\n");
			else
				printf("redirect_output(g_megabash)\n");
			return ;
		}
		i++;
	}
	// if (find_pipe(g_megabash.input) == TRUE)
	// 	pipe_treat(g_megabash, env);
	// else
		input_treat();
}
