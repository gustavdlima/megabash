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

	if (position > 0 && is_there_dollar(cmd, position) == FALSE)
		temp = ft_substr(cmd, 0, position);
	else
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

void	treat_dollar(char *cmd)
{
	char	*before;
	char	*interpreted;
	char	*now;
	int		begin;
	int		i;

	i = 0;
	while (cmd[i])
	{
		begin = i;
		if (cmd[i] == '\"')
		{
			if (double_quotted_argument(cmd + i) == TRUE)
			{
				i++;
				while (cmd[i] && cmd[i] != '\"')
				{
					if (cmd[i] == '$')
					{
						/*
						1. passar a parte anterior a isso para uma string
						2. acrescentar o content
						3. pular o name no cmd, para continuar analizando com base nisso
						4. ter variavel para guardar o que já foi tratado
						OBS. ISSO TEM QUE TÁ OK PRA UM LOOP, PELO AMOR DE DEUS
						*/
						// 1.
						if (now == NULL)
						{
							before = ft_substr(cmd, VARIAVEL QUE DIZ ONDE COMEÇOU O PROCESSAMENTO, i);
						}
						else
						{
							now = ft_substr(cmd, VARIAVEL QUE DIZ ONDE COMEÇOU O PROCESSAMENTO, i);
							before = ft_strjoin(treated, now);
							free (now);
						}
						// 2.
						interpreted = interpret_dollar(cmd + i);
						now = ft_strjoin(before, interpreted);
						free (before);
						free (interpreted);
					}
					i = i + jump_positions(cmd + i, i);
					begin = i;
				}
			}
		}
		if (unquotted_command(cmd + i) == TRUE)
		{

		}
		i++;
	}
}

void	treat_input(char **input)
{
	treat_space(*input);
	treat_quote(*input);
	printf("treat_quote = input : %s\n", *input);
	treat_dollar(*input);
}
