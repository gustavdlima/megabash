#include "minishell.h"

char	*get_name(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' || cmd[i] == ' ' || cmd[i] == '$' || cmd[i] == '\''
			|| cmd[i] == '\"' || cmd[i] == '}')
			break ;
		i++;
	}
	name = ft_substr(cmd, 0, i);
	i = 0;
	while (name[i])
	{
		if (ft_isascii(name[i]) != 0 && ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
			free (name);
			return (temp);
		}
		i++;
	}
	return (name);
}

