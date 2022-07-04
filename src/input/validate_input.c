#include "minishell.h"

int	validate_input(char *input)
{
	if (input)
	{
		if (!input[0] || only_space(input) == true)
			return (false);
		if (bash_syntax_error(input) == true)
			return (false);
		if (too_many_redirections(input) == true) // reescrever função para aceitar << e >>
			return (false);
		if (redirect_to_no_arguments(input) == true)
			return(false);
		if (different_redirection_signs(input) == true)
			return (false);
		return (true);
	}
	return (false);
}
// simbolos especiais juntos eh erro de syntax
