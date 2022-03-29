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
	// char	*aux;
	// size_t	where;
	size_t	i;

	i = wheres_dollar(cmd);
	*temp = ft_substr(cmd, 0, i);
	i--;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			if (single_quotted_argument(cmd, i) == FALSE)
			{
				name = interpret_dollar(cmd, i);
				// while (cmd[i] && cmd[i] != '\"')
				// 	i++;
			printf("NAME : %s\n", name);
			}
			else
			{
				while (cmd[i] && cmd[i] != '\'')
					i++;
				name = ft_substr(cmd, ft_strlen(*temp), i);
			printf("NAME : %s\n", name);
			}
			*sec_temp = ft_strjoin(*temp, name);
			printf("sec_temp : %s\n", *sec_temp);
			free (*temp);
		}
		// where = wheres_dollar(cmd + i);
		// aux = ft_substr(cmd, i, where);
		// 	printf("AUX : %s\n", aux);
		// if (!temp)
		// {
		// 	*temp = ft_strjoin(*sec_temp, aux);
		// 	printf("1. temp : %s\n", *temp);
		// 	free (*sec_temp);
		// 	free (aux);
		// }
		//  if (!sec_temp)
		// {
		// 	*sec_temp = ft_strdup(*temp);
		// 	free (*temp);
		// 	*temp = ft_strjoin(*sec_temp, aux);
		// 	printf("2. temp : %s\n", *temp);
		// 	free (aux);
		// 	free (*sec_temp);
		// }
		i++;
	}
	*final = ft_strdup(*temp);
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
