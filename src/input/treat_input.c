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

int	treat_dollar_input(char *cmd, char **final, char **temp, char **sec_temp, char *input)
{
	char	*name;
	char	*aux;
	size_t	i;

	i = wheres_dollar(cmd);
	*temp = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		if (cmd[i] == '$' && single_dollar(cmd + i) == FALSE)
		{
			if (single_quotted_argument(input, i) == FALSE)
			{
				if (is_question_mark(cmd + i) == TRUE)
				{
					name = ft_itoa(g_megabash.exit_status);
					i++;
				}
				else
				{
					name = interpret_dollar(cmd, i);
					i = i + jump_positions(cmd + i + 1);
					if (cmd[i] == '\0')
						break ;
				}
			}
			else
			{
				name = ft_substr(cmd, i, ft_int_strchr(cmd + i, '\''));
				i = i + ft_strlen(name) - 1;
			}
			*sec_temp = ft_strjoin(*temp, name);
			free (*temp);
			free (name);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		else
		{
			aux = ft_substr(cmd, i, 1);
			*sec_temp = ft_strjoin(*temp, aux);
			free (*temp);
			free (aux);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		i++;
	}
	*sec_temp = ft_strdup(*final);
	free (*final);
	*final = ft_strjoin(*sec_temp, *temp);
	free(*sec_temp);
	free(*temp);
	return (i);
}

char	*treat_dollar(char *cmd)
{
	char	*final;
	char	*temp;
	char	*second_temp;
	int		i;

	i = 0;
	final = ft_strdup("");
	while (cmd[i])
	{
		if (is_there_dollar(cmd + i, ft_strlen(cmd + i)) == TRUE)
			i = treat_dollar_input(cmd + i, &final, &temp, &second_temp, cmd)
				+ i;
		else
			i = treat_no_dollar_input(cmd + i, &final, &temp, &second_temp)
				+ i;
	}
	return (final);
}

int	is_operator(char *input)
{
	if (!ft_strncmp(input, "|", 2))
		return (IS_PIPE);
	else if (!ft_strncmp(input, ">", 2))
		return (IS_REDIRECT);
	else if (!ft_strncmp(input, "<", 2))
		return (IS_REDIRECT);
	else if (!ft_strncmp(input, ">>", 3))
		return (IS_REDIRECT);
	else if (!ft_strncmp(input, "<<", 3))
		return (IS_HERE_DOC);
	else
		return (FALSE);
}

int	check_operator(char operator)
{
	if (operator == '|')
		return (TRUE);
	else if (operator == '>')
		return (TRUE);
	else if (operator == '<')
		return (TRUE);
	else
		return (FALSE);
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
