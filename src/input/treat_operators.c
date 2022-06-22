#include "minishell.h"

static void	getting_temp_with_char(char **temp, char *input)
{
	char	*character;
	char	*str;

	character = ft_substr(input, 0, 1);
	str = ft_strjoin(*temp, character);
	free(*temp);
	*temp = ft_strdup(str);
	free(str);
	free(character);
}

static char	*double_operator(char *input, int i, int is_second_space)
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

static void	insert_space_after(char *input, int i, char **temp,
								int is_second_space)
{
	char	*str;
	char	*aux;

	if (input[i + 1] == input[i])
		aux = double_operator(input, i, is_second_space);
	else
	{
		if (is_second_space == true)
			aux = ft_strdup(" ");
		else
		{
			str = ft_substr(input + i, 0, 1);
			aux = ft_strjoin(str, " ");
			free (str);
		}
	}
	str = ft_strjoin(*temp, aux);
	free (*temp);
	free (aux);
	*temp = ft_strdup(str);
	free (str);
}

static void	insert_space_before(char *input, char **temp)
{
	char	*str;
	char	*aux;

	str = ft_substr(input, 0, 1);
	aux = ft_strjoin(" ", str);
	free (str);
	str = ft_strjoin(*temp, aux);
	free (aux);
	*temp = ft_strdup(str);
	free (str);
}

char	*check_operator_space(char *input)
{
	int		i;
	char	*temp;
	char	*aux;
	char	*auxiliar;

	i = -1;
	temp = ft_strdup("");
	while (input[++i])
	{
		if (check_operator(input[i]))
		{
			if (i != 0 && input[i - 1] && input[i - 1] != ' ')
			{
				insert_space_before(input + i, &temp);
				if (input[i + 1] != ' ' && input[i + 1])
					insert_space_after(input, i, &temp, true);
			}
			else if (input[i + 1] && input[i + 1] != ' ')

				insert_space_after(input, i, &temp, false);
			else
			{
				auxiliar = ft_substr(input + i, 0, 1);
				aux = ft_strjoin(temp, auxiliar);
				free(auxiliar);
				free(temp);
				temp = ft_strdup(aux);
				free(aux);
			}
		}
		else
			getting_temp_with_char(&temp, input + i);
		if (check_operator(input[i]) && (input[i + 1] == input[i]))
			i++;
	}
	return (temp);
}
