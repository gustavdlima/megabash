/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilson- <jmilson-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:51 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/20 20:21:35 by jmilson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*verify_pathway(char *pathways, char *cmd)
{
	char	*path_cmd;
	char	*temp;

	temp = ft_strjoin(pathways, "/");
	path_cmd = ft_strjoin(temp, cmd);
	if (access(path_cmd, F_OK) == 0)
	{
		free(temp);
		return (path_cmd);
	}
	free(temp);
	free(path_cmd);
	return (NULL);
}

static char	*path_whays(char **pathways, char *cmd)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (pathways[i])
	{
		if (!ft_strnstr(cmd, pathways[i], ft_strlen(pathways[i])))
		{
			path_cmd = verify_pathway(pathways[i], cmd);
			if (path_cmd)
			{
				free_matrix(pathways);
				return (path_cmd);
			}
		}
		else
		{
			free_matrix(pathways);
			if (access(cmd, F_OK) == 0)
				return (cmd);
		}
		i++;
	}
	free_matrix(pathways);
	return (NULL);
}

char	*what_cmd(char *cmd)
{
	t_env	*path;
	char	**pathways;
	char	*path_cmd;

	if (cmd == NULL)
		return (NULL);
	path = get_env_node(g_megabash.env, "PATH");
	if (path)
	{
		if ((cmd[0] == '.' || cmd[0] == '/') && access(cmd, F_OK) == 0)
			return (cmd);
		pathways = ft_split(path->content, ':');
		path_cmd = path_whays(pathways, cmd);
		if (path_cmd)
			return (path_cmd);
		return (NULL);
	}
	return (NULL);
}
