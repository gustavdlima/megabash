#include "minishell.h"

int	special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == 92 || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*interpret_dollar(char *cmd, int position)
{
	char	*interpreted;
	char	*temp;
	char	*rest;
	t_env	*env_var;
	int		jump;

	// if (cmd[position++] == '?')
	// 	return ("get_exit()");
	temp = ft_substr(cmd, 0, position);
	jump = jump_positions(cmd);
	if (!ft_isalnum(cmd[position + jump])) //O PROBLEMA TÁ AQUI DENTRO, PRECISA DE MAIS CONDIÇÕES CASO TENHA MAIS $
	{
		env_var = get_env_node(g_megabash.env, cmd);
		interpreted = ft_strjoin(temp, env_var->content);
		free (temp);
		temp = ft_strdup(interpreted);
		free (interpreted);
		rest = ft_substr(cmd, jump + position, ft_strlen(cmd)); //TEM MAIS $s???
		// PROCURAR EM "rest" MAIS $s
		interpreted = ft_strjoin(temp, rest);
		free (temp);
		free (rest);
		return (interpreted);
	}
	return (temp);
}

int	unquotted_line(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*metacharacters_treat(char *cmd)
{
	int	i;

	i = 0;
	if (double_closed_quotes(cmd) == TRUE)
	{
		while (cmd[i])
		{
			if (cmd[i] == 34)
			{
				i++;
				while (cmd[i])
				{
					if (cmd[i] == '$')
						return (interpret_dollar(cmd, i));
					i++;
				}
			}
			i++;
		}
	}
	else if (unquotted_line(cmd) == TRUE)
	{
		while (cmd[i])
		{
			if (cmd[i] == '$')
				return (interpret_dollar(cmd, i));
			i++;
		}
		if (special_or_metacharacters(cmd) == TRUE)
		{
			printf("Caractere especial ou metacaractere fora de aspas, NÃO PODE!\n");
		}
	}
	return(cmd);
}

