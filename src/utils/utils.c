#include "minishell.h"

char	*insert_caracter(char *cmd, char caracter)
{
	int		i;
	char	*new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 2));
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = caracter;
	i++;
	new_cmd[i] = '\0';
	free(cmd);
	return (new_cmd);
}

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
	if (s1)
		s1_len = ft_strlen(s1);
	else
		s1_len = 0;
	if (s2)
	{

		s2_len = ft_strlen(s2);
	}
	else
		s2_len = 0;
	if (s1_len != s2_len)
		return (false);
	while (s1[i] && s2[i] && i < s1_len)
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

int	is_alphabetic(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90)
			|| (str[i] >= 97 && str[i] <= 122) || str[i] == '_')
			return (0);
		else
			break ;
		i++;
	}
	return (1);
}
