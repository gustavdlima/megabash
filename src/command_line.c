#include "minishell.h"

char	*command_line(t_root *root)
{
	root->input = readline("megabash$ ");
	add_history(root->input);
	return(root->input);
}

char	*what_cmd(char *cmd)
{
	char	**pathways;
	char	*path_cmd;
	int		i;

	pathways = ft_split(PATH, ':');
	i = 0;
	while (pathways[i])
	{
		path_cmd = ft_strjoin(pathways[i], cmd);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	free(pathways);
	return (NULL);
}
