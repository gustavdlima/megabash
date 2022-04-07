#include "minishell.h"

char	*what_cmd(char *cmd)
{
	t_env	*path;
	char	*temp;
	char	**pathways;
	char	*path_cmd;
	int		i;

	i = 0;
	path = get_env_node(g_megabash.env, "PATH");
	pathways = ft_split(path->content, ':');
	while (pathways[i])
	{
		temp = ft_strjoin(pathways[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		if (access(path_cmd, F_OK) == 0)
		{
			free_matrix(pathways);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free(pathways);
	return (NULL);
}
