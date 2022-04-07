#include "minishell.h"

int	validate_input(char *input)
{
	// check_builtins
	// if (is_builtin(input) == TRUE)
	// {

	// }
	// checar se eh um comando valido pelo access
	if (input[0] == NULL)
	{
		g_megabash.exit_status = 137;
		return (FALSE);
	}
	if (ft_strlen(input) == 1 && input[0] != 'l' && ft_isalnum(input[0]))
	{
		printf("%c: command not found\n", input[0]);
		g_megabash.exit_status = 127;
		return (FALSE);
	}
	if (only_space(input) == TRUE)
	{
		g_megabash.exit_status = 127;
		return (FALSE);
	}
	if (open_curly_bracket(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: open curly bracket.", 2);
		g_megabash.exit_status = 130;
		return (FALSE);
	}
	if (input[0] == '|' || input[0] == ';' || input[0] == '<'
			|| input[0] == '>' || input[0] == '{' || input[0] == '}')
	{
		printf("Syntax error near unexpected token `%c'\n", input[0]);
		g_megabash.exit_status = 2;
		return (FALSE);
	}
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
	if (unquotted_special_metacharacters(input) == TRUE)
	{
		ft_putendl_fd("Syntax error: special or metacharacters on unquotted arguments.", 2);
		g_megabash.exit_status = 130;
		return (FALSE);
	}
	// erro de sintax
	// fd nao existir
	// repositorio n existir
	// so espaço
	// ta vazio??
	// cntrl v + tab = coloca tabulacao (nao pode ter nada na area de transferencia), guardar no hsitorico e nao fazer nada
	//cat | cat | ls
	return (TRUE);
}
