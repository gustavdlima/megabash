#include "minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$ ");
	add_history(input);
	return (input);
}
