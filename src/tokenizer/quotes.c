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

char	*no_quotes(char **cmd)
{
	char	*str;
	int		i;
	int		j;
	int		len;
	int		quotes;

	i = 0;
	j = 0;
	quotes = 0;
	printf(">>>>>>>>%s\n", *cmd);
	quotes_treat(*cmd);
	while (*cmd[i])
	{
		if (*cmd[i] == '\'' || *cmd[i] == '\"')
			quotes++;
		i++;
	}
	if (quotes != 0)
	{
		len = ft_strlen(*cmd);
		str = ft_calloc((len), sizeof(char));
		i = 0;
		while (*cmd[i])
		{
			while (*cmd[i] == '\'' || *cmd[i] == '\"')
				i++;
			str[j++] = *cmd[i++];
		}
		reverse_quotes_treat(str);
		return (str);
	}
	return (*cmd);
}
