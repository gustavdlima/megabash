#include "minishell.h"

void	treat_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'')
			{
				if (cmd[i] == '\"')
					cmd[i] = 2;
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"')
			{
				if (cmd[i] == '\'')
					cmd[i] = 3;
				i++;
			}
		}
		i++;
	}
}

void	treat_space(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] != sign && cmd[i])
			{
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		i++;
	}
}

char	*interpret_dollar(char *cmd, int position)
{
	t_env	*env_var;
	char	*before;
	char	*interpreted;
	char	*after;
	int		jump;

	before = ft_substr(cmd, 0, position);
	jump = jump_positions(cmd, position);
	if (!cmd[jump])
	{
		free(cmd);
		cmd = ft_strdup(before);
		free(before);
	}
	else if (!ft_isalnum(cmd[position + jump]))
	{
		env_var = get_env_node(g_megabash.env, cmd);
		interpreted = ft_strjoin(before, env_var->content);
		free (before);
	}
	else
	{
		position = position + jump;
		while (cmd[position])
		{
			if (cmd[position] == ' '|| cmd[position] == '$'
				|| special_or_metacharacters(cmd + position) == TRUE)
			{
				interpreted = ft_substr(cmd, position, ft_strlen(cmd));
				break ;
			}
			position++;
		}
	}
	free (cmd);
	after = ft_strjoin(before, interpreted);
	free (before);
	free (interpreted);
	return (after);
}

void	treat_dollar(char *cmd)
{
	char	*treated;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] && cmd[i] != '\"')
			{
				if (cmd[i] == '$')
				{
					treated = interpret_dollar(cmd, i);
				}
				i++;
			}
		}
		if (cmd[i] == '$')
			treated = interpret_dollar(cmd, i);
		i++;
	}
	printf("%s\n", treated);
}

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	treat_dollar(*input);
}
