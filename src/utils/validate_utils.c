#include "minishell.h"

int	no_words_after_redirect(char *input)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_split(input, ' ');
	int matrix_len = matrix_size(matrix);
	while (matrix[i])
	{
		if (i == matrix_len)
		{

			if (!matrix[i] || (ft_new_strncmp("|", matrix[i])) || (ft_new_strncmp("||", matrix[i])
				|| (ft_new_strncmp("&", matrix[i])) || (ft_new_strncmp("&&", matrix[i]))
				|| (ft_new_strncmp(">>", matrix[i])) || (ft_new_strncmp(">", matrix[i]))
				|| (ft_new_strncmp("<<", matrix[i])) || (ft_new_strncmp("<", matrix[i]))))
			{
				error_message("megabash: syntax error near unexpected token", 2);
				free_matrix(matrix);
				return (true);
			}
		}
		i++;
	}
	free_matrix(matrix);
	return (false);
}

static int	incrementing_i_for_single_quotes(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] && cmd[i] != '\'')
			i++;
		if (cmd[i] == '\'')
			i++;
	}
	return (i);
}

int	open_curly_bracket(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i = i + incrementing_i_for_single_quotes(cmd + i);
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '{')
			{
				while (cmd[i] && cmd[i] != '}' && cmd[i] != '\"'
					&& cmd[i] != '\'')
					i++;
				if (cmd[i] != '}')
					return (true);
				if (!cmd[i])
					break ;
			}
		}
		if (cmd[i])
			i++;
	}
	return (false);
}

int	open_quotes(char *cmd)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
				i++;
			if (cmd[i] != sign)
				return (true);
		}
		i++;
	}
	return (false);
}

int	bash_syntax_error(char *cmd)
{
	if (cmd[0] == '|' || cmd[0] == ';' || cmd[0] == '&')
	{
		printf("bash: syntax error near unexpected token `%c'\n", cmd[0]);
		g_megabash.exit_status = 2;
		return (true);
	}
	return (false);
}

int	command_not_found(char *cmd)
{
	if (ft_strlen(cmd) == 1 && cmd[0] != 'l' && ft_isascii(cmd[0]))
	{
		printf("%c: command not found\n", cmd[0]);
		g_megabash.exit_status = 127;
		return (true);
	}
	return (false);
}
