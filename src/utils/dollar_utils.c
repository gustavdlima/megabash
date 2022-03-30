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

int	counting_dollars(char *cmd)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			dollar++;
		i++;
	}
	return (dollar);
}

int	single_dollar(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == 1 || cmd[i] == ' ' || !cmd[i] || cmd[i] == '$')
		return(TRUE);
	return(FALSE);
}

int	is_question_mark(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[i] == '?')
		return (TRUE);
	return (FALSE);
}
