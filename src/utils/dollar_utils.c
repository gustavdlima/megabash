#include "minishell.h"

int	is_there_dollar(char *cmd, int max_i)
{
	int	i;

	i = 0;
	while (cmd[i] || i < max_i)
	{
		if (cmd[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*get_name(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '$' || cmd[i] == '\'' || cmd[i] == '\"')
		{
			i--;
			break ;
		}
		i++;
	}
	name = ft_substr(cmd, 0, i);
	i = 0;
	while (name[i])
	{
		if (ft_isascii(name[i]) && ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i - 1);
			free (name);
			return (temp);
		}
		i++;
	}
	return (name);
}

int	wheres_dollar(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*interpret_dollar(char *cmd, int position)
{
	char	*interpreted;
	char	*temp;
	char	*name;
	t_env	*env_var;

	temp = ft_strdup("");
	name = get_name(cmd + position + 1);
	env_var = get_env_node(g_megabash.env, name);
	if (env_var != NULL)
	{
		interpreted = ft_strjoin(temp, env_var->content);
		free (temp);
		return (interpreted);
	}
	return (temp);
}
