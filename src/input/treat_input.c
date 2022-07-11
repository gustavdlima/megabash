#include "minishell.h"

int	is_operator(char *input)
{
	if (!ft_strncmp(input, "|", 2))
		return (is_pipe);
	else if (!ft_strncmp(input, ">", 2))
		return (is_redirect);
	else if (!ft_strncmp(input, "<", 2))
		return (is_redirect);
	else if (!ft_strncmp(input, ">>", 3))
		return (is_redirect);
	else if (!ft_strncmp(input, "<<", 3))
		return (is_redirect);
	else
		return (false);
}

int	check_operator(char operator)
{
	if (operator == '|')
		return (true);
	else if (operator == '<')
		return (true);
	else if (operator == '>')
		return (true);
	else
		return (false);
}

char	*treat_operators(char *input)
{
	int		i;
	char	*treated_input;

	i = 0;
	while (input[i])
	{
		if (check_operator(input[i]))
		{
			treated_input = check_operator_space(input);
			free(input);
			return (treated_input);
		}
		else
			i++;
	}
	return (input);
}

void	treat_input_chars(char *input)
{
	treat_char(input, ' ', 1);
	treat_char(input, '>', 4);
	treat_char(input, '<', 5);
	treat_char(input, '|', 6);
}

void	treat_input_and_tokenizer(char **input)
{
	char	*treated;

	treated = treat_operators(*input);
	tokenizer(treated);
	free(treated);
	treat_token_list();
}

// a e i o u -> some o u
// a ee ii oo u -> some o u
// aa ee ii oo u -> nao some nada
// aa ee ii oo uu -> nao some nada
