#include "minishell.h"

int	validate_input(char *input)
{
	if (input)
	{
		if (g_megabash.exit_status == 42)
		{
			g_megabash.exit_status = 2;
			return (false);
		}
		if (!input[0] || only_space(input) == true)
			return (false);
		if (bash_syntax_error(input) == true)
			return (false);
		if (command_not_found(input) == true)
			return (false);
		if (open_curly_bracket(input) == true)
		{
			ft_putendl_fd("Syntax error: open curly bracket.", 2);
			g_megabash.exit_status = 130;
			return (false);
		}
		if (too_many_redirections(input) == true)
			return (false);
		if (redirect_to_no_arguments(input) == true)
			return(false);
		if (different_redirection_signs(input) == true)
			return (false);
	// if (unquotted_special_metacharacters(input) == true)
	// 	return (false);
	// erro de sintax
	// fd nao existir
	// repositorio n existir
	// cntrl v + tab = coloca tabulacao (nao pode ter nada na area de transferencia), guardar no hsitorico e nao fazer nada
	//cat | cat | ls
		return (true);
	}
	return (false);
}
