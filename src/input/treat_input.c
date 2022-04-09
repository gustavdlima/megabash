#include "minishell.h"

void	treat_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				if (cmd[i] == '\"')
					cmd[i] = 2;
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				if (cmd[i] == '\'')
					cmd[i] = 3;
				i++;
			}
		}
		i++;
	}
}

void	reverse_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 1)
			cmd[i] = ' ';
		i++;
	}
}

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

void	treat_space(char *cmd)
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
				if (cmd[i] == ' ')
					cmd[i] = 1;
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
			printf("Verifica single quotted: %s\n", cmd + i);
			if (single_quotted_argument(input, i) == FALSE) // INVALID READ OF SIZE = 0
			{
				if (is_question_mark(cmd + i) == TRUE)
				{
					name = ft_itoa(g_megabash.exit_status);
					i++;
				}
				else
				{
					name = interpret_dollar(cmd, i);
					printf("1 . NAME : %s\n", name);
					i = i + jump_positions(cmd + i + 1);
					if (cmd[i] == '\0')
						break ;
				}
			}
			else
			{
				name = ft_substr(cmd, i, ft_int_strchr(cmd + i, '\''));
					printf("AQUIIII 2 . NAME : %s\n", name);
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
			// i = i + ft_strlen(aux);
			*sec_temp = ft_strjoin(*temp, aux);
			free (*temp);
			free (aux);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
			// i = i + ft_strlen(cmd + i);
		}
		i++;
	}
	*sec_temp = ft_strdup(*final);
	free (*final);
	*final = ft_strjoin(*sec_temp, *temp); //Address is 0 bytes after a block of size 12 alloc'd AQUIII
	free (*sec_temp);
	free (*temp);
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
			i = treat_dollar_input(cmd + i, &final, &temp, &second_temp, cmd) + i; //INVALID READ OF SIZE = 0
		else
			i = treat_no_dollar_input(cmd + i, &final, &temp, &second_temp) + i;
	}
	return (final);
}

// static void	getting_temp_with_char(char **temp, char *input)
// {
// 	char	*character;
// 	char	*str;

// 	character = ft_substr(input, 0, 1);
// 	str = ft_strjoin(*temp, character);
// 	free(*temp);
// 	*temp = ft_strdup(str);
// 	free(str);
// 	free(character);
// }

// static char	*double_operator(char *input, int i, int is_second_space)
// {
// 	char	*aux;
// 	char	*str;

// 	if (is_second_space == TRUE)
// 		aux = ft_substr(input + i, 0, 1);
// 	else
// 		aux = ft_substr(input + i, 0, 2);
// 	str = ft_strjoin(aux, " ");
// 	free (aux);
// 	aux = ft_strdup(str);
// 	free (str);
// 	return (aux);
// }
// static void	insert_space_after(char *input, int i, char **temp,
// 								int is_second_space)
// {
// 	char	*str;
// 	char	*aux;

// 	if (input[i + 1] == input[i])
// 		aux = double_operator(input, i, is_second_space);
// 	else
// 	{
// 		if (is_second_space == TRUE)
// 			aux = ft_strdup(" ");
// 		else
// 		{
// 			str = ft_substr(input + i, 0, 1);
// 			aux = ft_strjoin(str, " ");
// 			free (str);
// 		}
// 	}
// 	str = ft_strjoin(*temp, aux);
// 	free (*temp);
// 	free (aux);
// 	*temp = ft_strdup(str);
// 	free (str);
// }

// static void	insert_space_before(char *input, char **temp)
// {
// 	char	*str;
// 	char	*aux;

// 	str = ft_substr(input, 0, 1);
// 	aux = ft_strjoin(" ", str);
// 	free (str);
// 	str = ft_strjoin(*temp, aux);
// 	free (aux);
// 	*temp = ft_strdup(str);
// 	free (str);
// }

// static char	*check_operator_space(char *input)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	temp = ft_strdup("");
// 	while (input[i])
// 	{
// 		if (check_operator(input[i])
// 			&& (input[i - 1] != ' ' || input[i + 1] != ' '))
// 		{
// 			if (input[i - 1] != ' ' && input[i - 1] != NULL)
// 			{
// 				insert_space_before(input + i, &temp);
// 				if (input[i + 1] != ' ' && input[i + 1] != NULL)
// 					insert_space_after(input, i, &temp, TRUE);
// 			}
// 			else if (input[i + 1] != ' ' && input[i + 1] != NULL)
// 				insert_space_after(input, i, &temp, FALSE);
// 		}
// 		else
// 			getting_temp_with_char(&temp, input + i);
// 		if (check_operator(input[i]) && (input[i + 1] == input[i]))
// 			i++;
// 		i++;
// 	}
// 	return (temp);
// }

// static char	*treat_operators(char *input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (check_operator(input[i]))
// 			return (check_operator_space(input));
// 		else
// 			i++;
// 	}
// 	return (input);
// }

void	treat_input(char **input)
{
	char	*treated;

	printf("0. input : %s\n", *input);
	treat_input_chars(*input);
	treated = treat_operators(*input);
	printf("1. treat_input_chars : %s\n", treated);
	tokenizer(treated);
	printf("2. tokenizer : %s\n", treated);
	printf("3. print_token : %s\n", treated);
	// printf("4. treat_token_list : %s\n", *input);
	treat_token_list();
	print_token(g_megabash.token_list);
	// reverse_space(*input);
}

// echo "oi" | ls -l > file |< file cat | cat > file
