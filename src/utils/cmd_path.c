/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:01:51 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:01:51 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_whays(char **pathways, char *cmd)
{
	int		i;
	char	*path_cmd;
	char	*temp;

	i = 0;
	while (pathways[i])
	{
		temp = ft_strjoin(pathways[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		if (access(path_cmd, F_OK) == 0)
		{
			free_matrix(pathways);
			free(temp);
			return (path_cmd);
		}
		free(temp);
		free(path_cmd);
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
	if (access(cmd, F_OK) == 0 && (!ft_strncmp("/", cmd, 1)
			|| !ft_strncmp("./", cmd, 2)))
		return (cmd);
	path = get_env_node(g_megabash.env, "PATH");
	if (path)
	{
		pathways = ft_split(path->content, ':');
		path_cmd = path_whays(pathways, cmd);
		return (path_cmd);
	}
	else
		return (NULL);
}
