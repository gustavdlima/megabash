#include "minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
	{
		free_megabash();
		exit (0);
	}
	if (!ft_strncmp(input, "exit", 4))
		exit_builtin(input);
	add_history(input);
	return (input);
}
