#include "minishell.h"

static int	incrementing(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '{')
	{
		while (cmd[i] && cmd[i] != '}')
			i++;
		return (i + 1);
	}
	else
	{
		while (cmd[i])
		{
			if (cmd[i] == '-' || cmd[i] == ' ' || cmd[i] == '$'
				|| cmd[i] == '\'' || cmd[i] == '\"')
				break ;
			i++;
		}
	}
	return (i);
}

int	jump_positions(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

	i = incrementing(cmd);
	name = ft_substr(cmd, 0, i);
	// dprintf(2, "jump_positions.name : %s\n", name);
	i = 0;
	while (name[i])
	{
		if (ft_isascii(name[i]) != 0 && name[i] != '_' && ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
	// dprintf(2, "jump_positions.temp : %s\n", temp);
			free (name);
			i = ft_strlen(temp);
			free (temp);
			return (i);
		}
		i++;
	}
	i = ft_strlen(name);
	free (name);
	return (i);
}
