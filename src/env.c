#include "minishell.h"

void	put_env_data(char *envp, t_env *env)
{
	env->name = get_env_name(envp);
	env->content = get_env_path(envp);
}

char	*get_env_path(char *envp)
{
	int			i;
	char		*sup;
	size_t		name_size;
	size_t		path_size;

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
	return (sup);
}

char	*get_env_name(char *envp)
{
	size_t	name_size;
	char	*sup;

	name_size = ft_int_strchr(envp, '=');
	sup = malloc((sizeof(char *) * name_size));
	ft_memcpy(sup, envp, (name_size));
	return(sup);
}

t_env	*environment(char **envp)
{
	int	i;
	t_env *list;

	i = 1;
	list = env_lstnew(get_env_name(envp[0]),
					get_env_path(envp[0]));
	while (envp[i])
	{
		env_addback(&list, env_lstnew(get_env_name(envp[i]),
					get_env_path(envp[i])));
		i++;
	}
	return (list);
}
