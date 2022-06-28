#include "minishell.h"

char	*get_name(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' || cmd[i] == ' ' || cmd[i] == '$' || cmd[i] == '\''
			|| cmd[i] == '\"' || cmd[i] == '}')
			break ;
		i++;
	}
	name = ft_substr(cmd, 0, i);
	i = 0;
	while (name[i])
	{
		if ((ft_isascii(name[i]) != 0) && name[i] != '_'
			&& ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
			free (name);
			return (temp);
		}
		i++;
	}
	return (name);
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

char	*double_operator(char *input, int i, int is_second_space)
{
	char	*aux;
	char	*str;

	if (is_second_space == true)
		aux = ft_substr(input + i, 0, 1);
	else
		aux = ft_substr(input + i, 0, 2);
	str = ft_strjoin(aux, " ");
	free (aux);
	aux = ft_strdup(str);
	free (str);
	return (aux);
}
