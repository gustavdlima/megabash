#include "minishell.h"

int	single_quotted_argument(char *cmd, int dollar)
{
	int	i;
	int	sign;
	int	begin;
	int	end;

	i = 0;
	sign = '\'';
	begin = 0;
	end = 0;
	while (cmd[i])
	{
		if (sign == cmd[i])
		{
			begin = i;
			i++;
			while (cmd[i] && cmd[i] != sign)
				i++;
			if (cmd[i] == sign)
				end = i;
		}
		i++;
	}
	if (end > begin && end > dollar && dollar > begin)
		return (TRUE);
	return (FALSE);
}

int	double_quotted_argument(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			sign = cmd[i];
			if (sign == '\"')
			{
				i++;
				while (cmd[i] && cmd[i] != sign)
					i++;
				if (cmd[i] == sign)
					return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

int	unquotted_command(char *cmd)
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

int	unquotted_dollar_argument(char *cmd)
{
	size_t	i;

	i = wheres_dollar(cmd);
	if (i == ft_strlen(cmd))
		return (FALSE);
	return (TRUE);
}

int	open_quotes(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
			{
				i++;
			}
			if (cmd[i] != sign)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
