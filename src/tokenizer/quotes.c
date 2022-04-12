#include "minishell.h"

int	single_quotted_argument(char *cmd, int dollar)
{
	char	sign;
	int		begin;
	int		end;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			begin = i;
			i++;
			while (cmd[i] && cmd[i] != sign)
				i++;
			end = i;
			if (dollar < end && dollar > begin && sign == '\'')
				return (TRUE);
			else if (dollar < end && dollar > begin && sign == '\"')
				return (FALSE);
		}
		i++;
	}
	return (FALSE);
}

int	open_quotes(char *cmd)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
				i++;
			if (cmd[i] != sign)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static int	is_there_quotes(char *cmd)
{
	int		quotes;
	int		i;

	i = 0;
	quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes++;
		i++;
	}
	return (quotes);
}

char	*no_quotes(char *cmd)
{
	char	*str;
	int		quotes;
	int		j;
	int		i;

	i = 0;
	quotes = is_there_quotes(cmd);
	if (quotes != 0)
	{
		str = ft_calloc((ft_strlen(cmd) - quotes + 1), sizeof(char));
		i = 0;
		j = 0;
		while (cmd[i])
		{
			while (cmd[i] == '\'' || cmd[i] == '\"')
				i++;
			str[j++] = cmd[i];
			if (cmd[i])
				i++;
		}
		free (cmd);
		return (str);
	}
	return (cmd);
}
