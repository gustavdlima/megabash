#include "minishell.h"

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i - 1);
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

int	ft_new_strncmp(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (FALSE);
	while (i < s1_len)
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
