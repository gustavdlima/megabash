#include "minishell.h"

int	only_space(char *cmd)
{
	int	i;
	int	space;
	int	cmd_len;

	i = 0;
	space = 0;
	cmd_len = ft_strlen(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\v' || cmd[i] == '\t'
			|| cmd[i] == '\r' || cmd [i] == ' ')
			space++;
		i++;
	}
	if (space == cmd_len)
		return (true);
	return (false);
}
