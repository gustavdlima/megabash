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
	i = 0;
	while (name[i])
	{
		if (ft_isascii(name[i]) != 0 && name[i] != '_'
			&& ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
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

static int	expand_dollar(char *cmd, int i, char **name)
{
	int		curly_bracket;
	int		skip;

	skip = 0;
	curly_bracket = 0;
	if (cmd[i + 1] == '{')
	{
		i++;
		skip++;
		curly_bracket = 1;
	}
	if (is_question_mark(cmd + i) == true)
	{
		*name = ft_itoa(g_megabash.exit_status);
		skip = skip + 2 + curly_bracket;
	}
	else
	{
		*name = interpret_dollar(cmd, i);
		skip = skip + jump_positions(cmd + i + 1) + 1 + curly_bracket;
	}
	return (skip);
}

char	*treat_dollar(char *cmd)
{
	char	*final;
	char	*temp;
	char	*name;
	int		i;

	i = wheres_dollar(cmd);
	final = ft_substr(cmd, 0, i);
	while (cmd[i])
	{
		if (cmd[i] == '$' && single_dollar(cmd + i) == false
			&& single_quotted_argument(cmd, i) == false)
			i = i + expand_dollar(cmd, i, &name);
		else
		{
			name = ft_substr(cmd + i, 0, 1);
			i++;
		}
		temp = ft_strjoin(final, name);
		free(final);
		free(name);
		final = ft_strdup(temp);
		free(temp);
	}
	free(cmd);
	return (final);
}
