#include "minishell.h"

void	validate_input(char *input)
{
	//não é builtin
	if (open_quotes(input) == TRUE)
	{
		ft_putendl_fd("Open quotes.", 2);
		g_megabash.exit_status = 130;
		exit (130);
	}
	if (unquotted_command(input) == TRUE
		&& special_or_metacharacters(input) == TRUE)
	{
		ft_putendl_fd("Forbidden characters on unquotted command.", 2);
		g_megabash.exit_status = 1;
		exit (1);
	}
	// pipe sem argumento
	// erro de sintax
}
