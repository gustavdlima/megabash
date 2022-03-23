#include "minishell.h"

char	*get_env_path(char *envp)
{
	int			i;
	char		*sup;
	int		name_size;
	int		path_size;

	i = 0;
	name_size = ft_int_strchr(envp, '=') + 1;
	path_size = ft_strlen(envp) - name_size;
	if (path_size == 0)
	{
		sup = ft_strdup("");
		return (sup);
	}
	sup = malloc(sizeof(char *) * path_size);
	while (envp[i])
	{
		sup[i] = envp[name_size];
		name_size++;
		i++;
	}
	sup[path_size] = '\0';
	return (sup);
}

char	*get_env_name(char *envp)
{
	int	name_size;
	char	*sup;

	name_size = ft_int_strchr(envp, '=');
	sup = malloc((sizeof(char *) * name_size));
	ft_memcpy(sup, envp, name_size);
	sup[name_size] = '\0';
	return(sup);
}

void	environment(char **envp)
{
	int	i;

	i = 1;
	g_megabash.env = env_lst_new(get_env_name(envp[0]),
									get_env_path(envp[0]));
	while (envp[i])
	{
		env_addback(&g_megabash.env, env_lst_new(get_env_name(envp[i]),
					get_env_path(envp[i])));
		i++;
	}
}
