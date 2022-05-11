#include "minishell.h"

void	reverse_char(char *cmd, int nbr, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == nbr)
			cmd[i] = c;
		i++;
	}
}

void	reverse_input_chars(char *input)
{
	reverse_char(input, 1, ' ');
	reverse_char(input, 2, '"');
	reverse_char(input, 3, '\'');
	reverse_char(input, 4, '>');
	reverse_char(input, 5, '<');
	reverse_char(input, 6, '|');
}

void	treat_input_chars(char *input)
{
	treat_char(input, ' ', 1);
	treat_char(input, '>', 4);
	treat_char(input, '<', 5);
	treat_char(input, '|', 6);
}

void	treat_char(char *cmd, char c, int nbr)
{
	int	i;
	int	sign;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] != sign && cmd[i])
			{
				if (cmd[i] == c)
					cmd[i] = nbr;
				i++;
			}
		}
		i++;
	}
}

static int	expand_dollar(char *cmd, int i, char **name)
{
	int		curly_bracket;
	int		skip;

	skip = 0;
	curly_bracket = 0;
	if (cmd[i + 1] == '{')
	{
		i++;
		skip++;
		curly_bracket = 1;
	}
	if (is_question_mark(cmd + i) == true)
	{
		*name = ft_itoa(g_megabash.exit_status);
		skip = skip + 2 + curly_bracket;
	}
	else
	{
		*name = interpret_dollar(cmd, i);
		skip = skip + jump_positions(cmd + i + 1) + 1 + curly_bracket;
	}
	return (skip);
}

char	*treat_dollar(char *cmd)
{
	char	*final;
	char	*temp;
	char	*name;
	int		i;

	i = wheres_dollar(cmd);
	final = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		if (cmd[i] == '$' && single_dollar(cmd + i) == false
			&& single_quotted_argument(cmd, i) == false)
			i = i + expand_dollar(cmd, i, &name);
		else
		{
			name = ft_substr(cmd + i, 0, 1);
			i++;
		}
		temp = ft_strjoin(final, name);
		free(final);
		free(name);
		final = ft_strdup(temp);
		free(temp);
	}
	return (final);
}

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
	int	i;

	i = 0;
	while (input[i])
	{
		if (check_operator(input[i]))
			return (check_operator_space(input));
		else
			i++;
	}
	return (input);
}

void	treat_input(char **input)
{
	char	*treated;

	treat_input_chars(*input);
	printf("treat_input_chars: %s\n", *input);
	treated = treat_operators(*input);
	printf("treat_operators : %s\n", treated);
	tokenizer(treated);
	treat_token_list();
}

// a e i o u -> some o u
// a ee ii oo u -> some o u
// aa ee ii oo u -> nao some nada
// aa ee ii oo uu -> nao some nada
