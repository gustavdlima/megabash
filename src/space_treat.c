#include "minishell.h"

char	*original_cmd(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(cmd);
	while (i < j)
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				if (cmd[i] == 1)
					cmd[i] = ' ';
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				if (cmd[i] == 1)
					cmd[i] = ' ';
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	*treating_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	**space_treat(char *input)
{
	char	**cmd;
	char	*to_treat;
	int		i;

	i = 0;
	to_treat = treating_cmd(input);
	cmd = ft_split(to_treat, ' ');
	if (!cmd)
		perror("Failed to process the command");
	while (cmd[i])
	{
		cmd[i] = original_cmd(cmd[i]);
		i++;
	}
	return(cmd);
}
