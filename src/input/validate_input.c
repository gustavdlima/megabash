#include "minishell.h"

int	validate_input(char *input)
{
	if (input)
	{
		if (g_megabash.exit_status == 42)
		{
			g_megabash.exit_status = 2;
			return (FALSE);
		}
		if (!input[0] || only_space(input) == TRUE)
			return (FALSE);
		if (bash_syntax_error(input) == TRUE)
			return (FALSE);
		if (command_not_found(input) == TRUE)
			return (FALSE);
		if (open_curly_bracket(input) == TRUE)
		{
			ft_putendl_fd("Syntax error: open curly bracket.", 2);
			g_megabash.exit_status = 130;
			return (FALSE);
		}
		if (too_many_redirections(input) == TRUE)
			return (FALSE);
		if (redirect_to_no_arguments(input) == TRUE)
			return(FALSE);
		if (different_redirection_signs(input) == TRUE)
			return (FALSE);
	// if (unquotted_special_metacharacters(input) == TRUE)
	// 	return (FALSE);
	// erro de sintax
	// fd nao existir
	// repositorio n existir
	// cntrl v + tab = coloca tabulacao (nao pode ter nada na area de transferencia), guardar no hsitorico e nao fazer nada
	//cat | cat | ls
		return (TRUE);
	}
	return (FALSE);
}
