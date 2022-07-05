#include "minishell.h"

char	*get_env_path(char *envp)
{
	const char *temp = ft_strchr(envp, '=') + 1;
	const char *sup = ft_strdup(temp);

	return ((char *)sup);
}

char	*get_env_name(char *envp)
{
	const int	name_size = ft_int_strchr(envp, '=');
	char	*sup;

	sup = malloc((sizeof(char *) * name_size));
	ft_memcpy(sup, envp, name_size);
	sup[name_size] = '\0';
	return (sup);
}

void	environment(char **envp)
{
	char	*temp_name;
	char	*temp_path;
	int		i;

	i = 0;
	g_megabash.envp = envp;
	while (envp[i])
	{
		temp_name = get_env_name(envp[i]);
		temp_path = get_env_path(envp[i]);
		env_addback(&g_megabash.env, env_lst_new(temp_name, temp_path));
		free(temp_name);
		free(temp_path);
		i++;
	}
}
