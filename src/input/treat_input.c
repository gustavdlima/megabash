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

int	treat_dollar_input(char *cmd, char **final, char **temp, char **sec_temp)
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
			if (single_quotted_argument(cmd, i) == FALSE)
			{
				if (is_question_mark(cmd + i) == TRUE)
				{
					name = ft_itoa(g_megabash.exit_status);
					i++;
				}
				else
				{
					name = interpret_dollar(cmd, i);
					aux = get_name(cmd + i + 1);
					i = i + ft_strlen(aux);
					free (aux);
				}
			}
			else
			{
				name = ft_substr(cmd, i, ft_int_strchr(cmd + i, '\''));
				i = i + ft_strlen(name) - 1;
			}
			*sec_temp = ft_strjoin(*temp, name);
			free (*temp);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		else
		{
			aux = ft_substr(cmd, i, 1);
			*sec_temp = ft_strjoin(*temp, aux);
			free (*temp);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		i++;
	}
	*sec_temp = ft_strdup(*final);
	free (*final);
	*final = ft_strjoin(*sec_temp, *temp);
	// free (*sec_temp);
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
			i = treat_dollar_input(cmd + i, &final, &temp, &second_temp) + i;
		else
			i = treat_no_dollar_input(cmd + i, &final, &temp, &second_temp) + i;
	}
	return (final);
}

void	treat_input(char **input)
{
	char	*aux;

	(void)aux;
	printf("0. input : %s\n", *input);
	treat_space(*input);
	printf("1. SPACE input : %s\n", *input);
	treat_quote(*input);
	printf("2. QUOTE input : %s\n", *input);
	*input = treat_dollar(*input);
	printf("3. DOLLAR input : %s\n", *input);
	*input = no_quotes(*input);
	printf("4. REVERSE QUOTES input : %s\n", *input);
	reverse_space(*input);
	printf("5. REVERSE SPACE input : %s\n", *input);
}
