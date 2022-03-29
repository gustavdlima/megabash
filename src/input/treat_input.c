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
	// no_quotes(&cmd);
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

void	treat_dollar_input(char *cmd, char **final, char **temp, char **sec_temp)
{
	char	*name;
	char	*aux;
	size_t	i;

	i = wheres_dollar(cmd);
	*temp = ft_substr(cmd, 0, i);
			printf("TEMP : %s\n", *temp);
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (single_quotted_argument(cmd, i) == FALSE)
			{
				name = interpret_dollar(cmd, i);
				// aux = ft_substr(cmd, ft_strlen(*temp), i);
				aux = get_name(cmd + i + 1);
				printf("AUX: %s\n", aux);
				i = i + ft_strlen(aux);
				free (aux);
			printf("NAME : %s\n", name);
			}
			else
			{
				name = ft_substr(cmd, i, ft_int_strchr(cmd + i, '\''));
				i = i + ft_strlen(name) - 1;
			printf("NAME : %s\n", name);
			}
			*sec_temp = ft_strjoin(*temp, name);
			printf("sec_temp : %s\n", *sec_temp);
			free (*temp);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		else
		{
			aux = ft_substr(cmd, i, 1);
				printf("X. AUX: %s\n", aux);
			*sec_temp = ft_strjoin(*temp, aux);
			printf("X. sec_temp : %s\n", *sec_temp);
			free (*temp);
			*temp = ft_strdup(*sec_temp);
			free (*sec_temp);
		}
		i++;
	}
	*sec_temp = ft_strdup(*final);
	free (*final);
	*final = ft_strjoin(*sec_temp, *temp);
	free (*temp);
}

void	treat_dollar(char *cmd)
{
	char	**input;
	char	*final;
	char	*temp;
	char	*second_temp;
	int		i;

	i = 0;
	input = ft_split(cmd, ' ');
	final = ft_strdup("");
	while (input[i])
	{
		if (is_there_dollar(input[i], ft_strlen(input[i])) == TRUE)
			treat_dollar_input(input[i], &final, &temp, &second_temp);
		else
		{
			temp = ft_strdup(input[i]);
			second_temp = ft_strdup(final);
			free (final);
			final = ft_strjoin(second_temp, temp);
			free (temp);
			free (second_temp);
		}
		i++;
		if (input[i] != NULL)
		{
			temp = ft_strdup(final);
			free (final);
			final = ft_strjoin(temp, " ");
			free (temp);
		}
	}
	printf("final : %s\n", final);
}

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	treat_dollar(*input);
}
