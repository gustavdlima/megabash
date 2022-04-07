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

void    reverse_char(char *cmd, int nbr, char c)
{
    int    i;

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

void    treat_char(char *cmd, char c, int nbr)
{
    int    i;
    int    sign;

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
					g_megabash.exit_status = 0;
					i++;
				}
				else
				{
					name = interpret_dollar(cmd, i);
					printf("1 . NAME : %s\n", name);
					aux = get_name(cmd + i + 1);
					i = i + ft_strlen(aux);
					free (aux);
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

void	treat_input(char **input)
{
	printf("0. input : %s\n", *input);

	treat_input_chars(*input);

	tokenizer(*input);
	print_token(g_megabash.token_list);
	treat_token_list();
	// reverse_space(*input);
}

// echo "oi" | ls -l > file |  < file cat | cat > file
