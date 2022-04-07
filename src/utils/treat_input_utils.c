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
	printf("get_name = name : %s\n", name);
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

int	treat_no_dollar_input(char *cmd, char **final, char **temp, char **sec_temp)
{
	int	i;

	i = ft_strlen(cmd);
	*temp = ft_strdup(cmd);
	*sec_temp = ft_strdup(*final);
	free (*final);
	*final = ft_strjoin(*sec_temp, *temp);
	free (*temp);
	free (*sec_temp);
	return (i);
}
