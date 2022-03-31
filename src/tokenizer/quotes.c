#include "minishell.h"

int	single_quotted_argument(char *cmd, int dollar)
{
	char	sign;
	int		begin;
	int		i;

	i = dollar;
	begin = 0;
		printf("Where's the begin?\n");
	while (i >= 0)
	{
		printf("cmd[%d] : %c\n", i, cmd[i]);
		if (cmd[i] == ' ')
		{
		printf("HERE! : cmd[%d] : %c\n", i, cmd[i]);
			begin = i;
			break ;
		}
		i--;
	}
	i = begin;
	while (cmd[i])
	{
		printf("Quotes?\n");
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
		printf("SURE! : cmd[%d] : %c\tsign is %c\n", i, cmd[i], sign);
			while (cmd[i] && cmd[i] != sign)
				i++;
		printf("sign is %c\n", sign);
			if (cmd[i] == sign && sign == '\'')
				return (TRUE);
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

char	*reverse_quotes_treat(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 3)
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
		printf("len : %d\n", len);
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
	// printf("cmd : %s\nstr : %s\n", cmd, str);
		str = reverse_quotes_treat(str);
		// printf("cmd : %s\nstr : %s\n", cmd, str);
		free (cmd);
		return(str);
	}
	return (cmd);
}

int	ft_new_strncmp(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (FALSE);
	while (i < s1_len)
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}
