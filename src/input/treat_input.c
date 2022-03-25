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

char	*get_name(char *cmd)
{
	char	**input;
	char	*name;
	char	*temp;
	int		jump;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '$')
		{
			i--;
			break ;
		}
		i++;
	}
	name = ft_substr(cmd, 1, i);
	if (special_or_metacharacters(name) == TRUE)
	{
		printf("oi?\n");
		jump = jump_special_or_metacharacters(name);
		temp = ft_substr(name, 0, jump);
		free (name);
		return (temp);
	}
	return (name);
}

char	*interpret_dollar(char *cmd, int position)
{
	char	*interpreted;
	char	*complete;
	char	*temp;
	char	*name;
	t_env	*env_var;

	if (position > 0)
		temp = ft_substr(cmd, 0, position);
	else
		temp = ft_strdup("");
	name = get_name(cmd + position++);
	printf("name: %s\n", name);
	env_var = get_env_node(g_megabash.env, name);
	printf("env_var: %s\n", env_var->name);
	if (env_var != NULL)
	{
		interpreted = ft_strjoin(temp, env_var->content);
		free (temp);
	}
	if (ft_strncmp(cmd, (cmd + position + ft_strlen(name)), ft_strlen(cmd)) > 0)
	{
		temp = ft_substr(cmd, position + ft_strlen(name), ft_strlen(cmd));
		complete = ft_strjoin(interpreted, temp);
		free (interpreted);
		free (temp);
		return (complete);
	}
	return (temp);
}

void	treat_dollar(char *cmd)
{
	char	*treat;
	char	*treated;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strdup("");
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] && cmd[i] != '\"')
			{
				if (cmd[i] == '$')
				{
					printf("1\n");
					treat = interpret_dollar(cmd, i);
					printf("TREATED: %s\n", treat);
					treated = ft_strjoin(temp, treat);
					free (temp);
					temp = ft_strdup(treat);
					free (treat);
				}
				i++;
			}
		}
		if (cmd[i] == '$')
		{
					printf("2\n");
			treat = interpret_dollar(cmd, i);
			printf("TREATED: %s\n", treat);
			treated = ft_strjoin(temp, treat);
			free (temp);
			temp = ft_strdup(treat);
			free (treat);
		}
		i++;
	}
	free (temp);
	printf("%s\n", treated);
}

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	treat_dollar(*input);
}
