#include "minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_int_strchr(const char *s, int c)
{
	int		index;
	char	character;

	index = 0;
	character = (char)c;
	while (s[index] != '\0')
	{
		if (s[index] == character)
			return (index);
		index++;
	}
	if (character == '\0')
		return (index);
	return (0);
}
