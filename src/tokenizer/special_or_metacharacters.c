/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_or_metacharacters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:17 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:01:17 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_special_or_metacharacters(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == 92 || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#' || cmd[i] == '[' || cmd[i] == ']')
			break ;
		i++;
	}
	return (i);
}

int	special_or_metacharacters(char c)
{
	if (ft_isascii(c) != false && ft_isalnum(c) == false)
		return (true);
	return (false);
}

int	wheres_special_metacharacter(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ';' || cmd[i] == '\\' || cmd[i] == '(' || cmd[i] == ')'
			|| cmd[i] == '&' || cmd[i] == '#' || cmd[i] == '[' || cmd[i] == ']')
			return (i);
		i++;
	}
	return (i);
}

int	unquotted_special_metacharacters(char *cmd)
{
	int		i;
	int		sign;

	i = 0;
	while (cmd[i])
	{
		if (special_or_metacharacters(cmd[i]) == true)
		{
			ft_putendl_fd
			("Syntax error: special or metacharacters on unquotted arguments.",
			2);
			g_megabash.exit_status = 130;
			return (true);
		}
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] != sign)
				i++;
		}
		i++;
	}
	return (false);
}
