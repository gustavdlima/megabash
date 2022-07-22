/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:02:12 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/22 19:19:47 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	stop_on_some_chars(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' || cmd[i] == ' ' || cmd[i] == '$' || cmd[i] == '\''
			|| cmd[i] == '\"' || cmd[i] == '}')
			break ;
		i++;
	}
	return (i);
}

char	*get_name(char *cmd)
{
	char	*name;
	char	*temp;
	int		i;

	i = stop_on_some_chars(cmd);
	name = ft_substr(cmd, 0, i);
	i = 0;
	while (name[i])
	{
		if ((ft_isascii(name[i]) != 0) && name[i] != '_'
			&& ft_isalnum(name[i]) == 0)
		{
			temp = ft_substr(name, 0, i);
			free (name);
			return (temp);
		}
		i++;
	}
	return (name);
}

void	treat_char(char *cmd, char c, int nbr)
{
	int	i;
	int	sign;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			sign = cmd[i];
			i++;
			while (cmd[i] && cmd[i] != sign)
			{
				if (cmd[i] == c)
					cmd[i] = nbr;
				i++;
			}
		}
		if (cmd[i])
			i++;
	}
}

char	*double_operator(char *input, int i, int is_second_space)
{
	char	*aux;
	char	*str;

	if (is_second_space == true)
		aux = ft_substr(input + i, 0, 1);
	else
		aux = ft_substr(input + i, 0, 2);
	str = ft_strjoin(aux, " ");
	free (aux);
	aux = ft_strdup(str);
	free (str);
	return (aux);
}
