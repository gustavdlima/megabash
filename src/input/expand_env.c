#include "minishell.h"

int	jump_positions(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

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
			if (cmd[i] == '-' || cmd[i] == ' ' || cmd[i] == '$' || cmd[i] == '\''
			|| cmd[i] == '\"')
				break ;
			i++;
		}
	}
	name = ft_substr(cmd, 0, i);
	printf("JUMP = name : %s\n", name);
	i = 0;
	while (name[i])
	{
		if (ft_isascii(name[i]) != 0 && ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
			free (name);
			i = ft_strlen(temp);
	printf("JUMP = TEMP : %s\n", temp);
			return (i);
		}
		i++;
	}
	i = ft_strlen(name);
	free (name);
	return (i);
}
