#include "minishell.h"

static void	getting_spaced_input_with_char(char **temp, char *input)
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

void	adding_space_to_input(char *input, char **temp, int i)
{
	char	*aux;
	char	*auxiliar;

	if (i != 0 && input[i - 1] && input[i - 1] != ' ')
	{
		insert_space_before(input + i, temp);
		if (input[i + 1] != ' ' && input[i + 1])
			insert_space_after(input, i, temp, true);
	}
	else if (input[i + 1] && input[i + 1] != ' ')
		insert_space_after(input, i, temp, false);
	else
	{
		auxiliar = ft_substr(input + i, 0, 1);
		aux = ft_strjoin(*temp, auxiliar);
		free(auxiliar);
		free(*temp);
		*temp = ft_strdup(aux);
		free(aux);
	}
}

char	*check_operator_space(char *input)
{
	int		i;
	char	*spaced_input;

	i = -1;
	spaced_input = ft_strdup("");
	while (input[++i])
	{
		if (check_operator(input[i]))
			adding_space_to_input(input, &spaced_input, i);
		else
			getting_spaced_input_with_char(&spaced_input, input + i);
		if (check_operator(input[i]) && (input[i + 1] == input[i]))
			i++;
	}
	return (spaced_input);
}
