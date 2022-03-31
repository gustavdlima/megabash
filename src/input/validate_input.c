#include "minishell.h"

int	validate_input(char *input)
{
	//não é builtin
	if (open_quotes(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: open quotes.", 2);
		g_megabash.exit_status = 130;
		return (FALSE);
	}
	if (pipe_no_arguments(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: not enough arguments to pipe.", 2);
		g_megabash.exit_status = 130;
		return (FALSE);
	}
// <, <<, >> e > sozinhos erro de sintaxe (2)
	// erro de sintax
	// fd nao existir
	// repositorio n existir
	// so espaço
	// ta vazio??
	// cntrl v + tab = coloca tabulacao (nao pode ter nada na area de transferencia), guardar no hsitorico e nao fazer nada
	//cat | cat | ls
	return (TRUE);
}
