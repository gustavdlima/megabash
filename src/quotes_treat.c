#include "minishell.h"

int	double_closed_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34)
		{
			while (cmd[i] && cmd[i] != 34)
				i++;
			if (cmd[i] == 34)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*reverse_quotes_treat(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 1)
		{
			cmd[i] = '\'';
		}
		else if (cmd[i] == 2)
		{
			cmd[i] = '\"';
		}
		i++;
	}
	return (cmd);
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

int	matching_quotes(char *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
			{
				i++;
			}
			if (cmd[i] != sign)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

char	*no_quotes(char *cmd)
{
	char	*str;
	int		i;
	int		j;
	int		len;
	int		quotes;

	i = 0;
	j = 0;
	quotes = 0;
	printf(">>>>>>>>%s\n", cmd);
	quotes_treat(cmd);
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes != 0)
	{
		len = ft_strlen(cmd);
		str = ft_calloc((len), sizeof(char));
		i = 0;
		while (cmd[i])
		{
			while (cmd[i] == '\'' || cmd[i] == '\"')
				i++;
			str[j++] = cmd[i++];
		}
		reverse_quotes_treat(str);
		return (str);
	}
	return (cmd);
}
