#include "minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	if (!ft_strncmp(input, "exit", 4))
		exit_builtin(input);
	add_history(input);
	return (input);
}
