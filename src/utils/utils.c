#include "minishell.h"

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
