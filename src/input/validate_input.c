#include "minishell.h"

void	validate_input(char *input)
{
	//não é builtin
	if (open_quotes(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: open quotes.", 2);
		g_megabash.exit_status = 130;
	}
	if (unquotted_command(input) == TRUE
		&& special_or_metacharacters(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: special or metacharacters on unquotted command.", 2);
		g_megabash.exit_status = 130;
	}
	if (pipe_no_arguments(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: not enough arguments to pipe.", 2);
		g_megabash.exit_status = 130;
	}
	// erro de sintax
	// fd nao existir
	// repositorio n existir
	//
}
