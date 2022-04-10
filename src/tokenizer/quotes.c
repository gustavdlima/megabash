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

char	*quotes_treat(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd) - 1;
	while (cmd[i])
	{
		if (cmd[i] == 39)
		{
			i++;
			while (cmd[i] != 39 && i != 0 && i != len)
			{
				if (cmd[i] == 34)
				{
					cmd[i] = 2;
				}
				i++;
			}
		}
		if (cmd[i] == 34)
		{
			i++;
			while (cmd[i] != 34 && i != 0 && i != len)
			{
				if (cmd[i] == 39)
				{
				cmd[i] = 1;
				}
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	*no_quotes(char *cmd)
{
	int	quotes;
	int		j;
	int	len;
	char	*str;
	int		i;
	int		k;

	i = 0;
	quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes != 0)
	{
		len = ft_strlen(cmd) - quotes + 1;
		str = ft_calloc((len), sizeof(char));
		k = 0;
		j = 0;
		while (cmd[k]) //INVALID READ OF SIZE AQUIII
		{
			while (cmd[k] == '\'' || cmd[k] == '\"')
				k++;
			str[j++] = cmd[k];
			if (cmd[k])
				k++;
		}
		free (cmd);
		return(str);
	}
	return (cmd);
}
