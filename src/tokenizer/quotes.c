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
				return (true);
			else if (dollar < end && dollar > begin && sign == '\"')
				return (false);
		}
		i++;
	}
	return (false);
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

static int	hide_quotes_arguments(char *cmd, int quote, int quote_to_hide,
								int nbr)
{
	int	i;

	i = 1;
	while (cmd[i] != quote)
	{
		if (cmd[i] == quote_to_hide)
			cmd[i] = nbr;
		i++;
	}
	return (i);
}

void	treat_quote(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			i = i + hide_quotes_arguments(cmd + i, '\'', '\"', 2);
		if (cmd[i] == '\"')
			i = i + hide_quotes_arguments(cmd + i, '\"', '\'', 3);
		i++;
	}
}
