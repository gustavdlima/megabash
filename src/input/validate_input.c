#include "minishell.h"

int	validate_input(char *input)
{
	treat_input_chars(input);
	if (input)
	{
		if (!input[0] || only_space(input) == true)
			return (false);
		else if (bash_syntax_error(input) == true)
			return (false);
		else if (too_many_redirections(input) == true) // reescrever função para aceitar << e >>
			return (false);
		else if (redirect_to_no_arguments(input) == true)
			return(false);
		else if (different_redirection_signs(input) == true)
			return (false);
		else if (no_words_after_redirect(input) == true)
			return (false);
		// else if (too_many_pipes(input) == true)
		// 	return (false);
		return (true);
	}
	return (false);
}
