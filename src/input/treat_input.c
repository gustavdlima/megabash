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
			// printf("temp de name: %s\n", temp);
			free (name);
			return (temp);
		}
		i++;
	}
	return (name);
}

int	until_dollar(char *cmd, int begin)
{
	while (cmd[begin])
	{
		if (cmd[begin] == '$')
		{
			begin--;
			return (begin);
		}
		begin++;
	}
	return (ft_strlen(cmd));
}

char	*interpret_dollar(char *cmd, int position)
{
	char	*interpreted;
	char	*temp;
	char	*name;
	t_env	*env_var;

	temp = ft_strdup("");
	// printf("TEMP: %s\n", temp);
	name = get_name(cmd + position + 1);
	// printf("name: %s\n", name);
	env_var = get_env_node(g_megabash.env, name);
	// printf("env_var: %s\n", env_var->name);
	if (env_var != NULL)
	{
		interpreted = ft_strjoin(temp, env_var->content);
		// printf("interpreted : %s\n", interpreted);
		free (temp);
		return (interpreted);
	}
	return (temp);
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
	return (ft_strlen(cmd));
}

void	treat_dollar(char *cmd)
{
	char	**input;
	char	*final;
	char	*temp;
	char	*second_temp;
	int		i;

	i = 0;
	input = ft_split(cmd, ' ');
	final = ft_strdup("");
	while (input[i])
	{
		if (is_there_dollar(input[i], ft_strlen(input[i])) == TRUE)
		{
			temp = ft_substr(input[i], 0, wheres_dollar(input[i]));
			second_temp = ft_strjoin(final, temp);
			free (final);
			free (temp);
			if (single_quotted_argument(input[i]) == TRUE)
				temp = get_name(input[i]);
			else
				temp = interpret_dollar(input[i], wheres_dollar(input[i]));
			final = ft_strjoin(second_temp, temp);
			free (second_temp);
			free (temp);
			temp = ft_substr(input[i], ft_strlen(get_name(input[i])),
				ft_strlen(input[i]));
			second_temp = ft_strdup(final);
			free (final);
			final = ft_strjoin(second_temp, temp);
			free (second_temp);
			free (temp);
		}
		else
		{
			printf("NÃO tem dolar o3o\n");
			temp = ft_strdup(input[i]);
			second_temp = ft_strdup(final);
			free (final);
			final = ft_strjoin(second_temp, temp);
			free (temp);
			free (second_temp);
		}
		i++;
		if (input[i] != NULL)
		{
			temp = ft_strdup(final);
			final = ft_strjoin(temp, " ");
			free (temp);
		}
	}
	printf("final : %s\n", final);
}

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	treat_dollar(*input);
}
