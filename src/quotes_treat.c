#include "minishell.h"

char	*reverse_quotes_treat(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 1) //oi' ''   " oioioioii" " "'" considerar o que vem antes também pra não dar b.o quando for '"' 'oi
		{
			printf("cccccccccccccccccccccccccc\n");
			cmd[i] = '\'';
		}
		else if (cmd[i] == 2)
		{
			printf("ddddddddddddddddddddddddddd\n");
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
		if (cmd[i] == 39 && i != 0 && i != len) //oi' ''   " oioioioii" " "'" considerar o que vem antes também pra não dar b.o quando for '"' 'oi
		{
			printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
			cmd[i] = 1;
		}
		else if (cmd[i] == 34 && i != 0 && i != len)
		{
			printf("BBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
			cmd[i] = 2;
		}
		i++;
	}
	return (cmd);
}

int	wheres_quote(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd) - 1;
	while (cmd[i])
	{
		if (cmd[i] == 39) //oi' ''   " oioioioii" " "'" considerar o que vem antes também pra não dar b.o quando for '"' 'oi'
		{
			i++;
			while(cmd[i] && cmd[i] != 39)
				i++;
			if (cmd[i] == '\0')
			{
				if(cmd[0] == 39 || cmd[len] == 39)
				{
					return (1);
				}
			}
		}
		else if (cmd[i] == 34)
		{
			i++;
			while(cmd[i] && cmd[i] != 34)
				i++;
			if (cmd[i] == '\0')
			{
				if(cmd[0] == 34 || cmd[len] == 34)
				{
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}

int	matching_quotes(char *cmd)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39)
			single_quotes++;
		if (cmd[i] == 34)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0)
	{
		if (wheres_quote(cmd) == 1)
			return (1);
	}
	if (double_quotes % 2 != 0)
	{
		if (wheres_quote(cmd) == 1)
			return (1);
	}
	return (0);
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
		reverse_quotes_treat(cmd);
		printf("oi?\n");
		return (str);
	}
	return (cmd);
}
