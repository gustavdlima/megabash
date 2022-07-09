#include "minishell.h"

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
