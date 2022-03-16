#include "minishell.h"

void	command_line(t_root *root)
{
	root->input = readline("megabash$ ");
	if (theres_delimiter(root->input) == FALSE)
		add_history(root->input);
}

char	*what_cmd(char *cmd, t_env *env)
{
	t_env	*path;
	char	*temp;
	char	**pathways;
	char	*path_cmd;
	int		i;

	path = env_node(env, "PATH", 5);
	pathways = ft_split(path->content, ':');
	i = 0;
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
