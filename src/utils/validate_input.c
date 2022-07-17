/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:39:42 by jmilson-          #+#    #+#             */
/*   Updated: 2022/07/17 04:13:06 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_quotes(char *cmd)
{
	int	quotes;
	int	len_cmd;
	int	i;

	len_cmd = ft_strlen(cmd);
	quotes = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			quotes++;
		if (cmd[i] == '.')
			quotes++;
		i++;
	}
	if (quotes >= len_cmd)
		return (true);
	return (false);
}
