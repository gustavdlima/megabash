/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_redirect_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:02:21 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:02:21 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_arguments(char *cmd)
{
	char	*temp;

	if (ft_strlen(cmd) < 1)
		return (true);
	if (only_space(cmd) == true)
		return (true);
	if (!cmd)
		return (true);
	else
	{
		temp = ft_strtrim(cmd, " ");
		if (temp)
		{
			free(temp);
			return (false);
		}
		free(temp);
	}
	return (false);
}

int	redirect_to_pipe(char *cmd)
{
	char	*temp;

	temp = ft_strtrim(cmd, " ");
	if (temp)
	{
		if (temp[0] == '|')
		{
			free(temp);
			return (true);
		}
		if (temp)
			free(temp);
	}
	return (false);
}

int	redirect_to_no_arguments(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			if (no_arguments(cmd + i) == true)
			{
				error_message
				("megabash: syntax error near unexpected token `newline'", 2);
				return (true);
			}
		}
		if (cmd[i])
			i++;
	}
	return (false);
}

static int	more_redirections(char *cmd, int sign)
{
	if (cmd[0] && (cmd[0] == '>' || cmd[0] == '<'))
	{
		dprintf(2, "bash: syntax error near unexpected token`%c'\n", sign);
		g_megabash.exit_status = 2;
		return (true);
	}
	return (false);
}

int	too_many_redirections(char *cmd)
{
	int	sign;
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			sign = cmd[i];
			i++;
			if (cmd[i] == '>' || cmd[i] == '<')
				i++;
			if (cmd[i])
			{
				while (cmd[i] && cmd[i] == ' ')
					i++;
				if (more_redirections(cmd + i, sign))
					return (true);
			}
		}
		if (cmd[i])
			i++;
	}
	return (false);
}
