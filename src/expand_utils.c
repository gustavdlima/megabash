#include "minishell.h"

int	jump_positions(char *cmd, t_env *env)
{
	int		len;

	while (env)
	{
		len = ft_strlen(env->name) + 1;
		if(ft_strnstr(cmd, env->name, ft_strlen(cmd)) != NULL)
			return (len);
		env = env->next;
	}
	return (0);
}

struct s_env	*get_env_content_(char *cmd, t_env *env)
{
	while (env)
	{
		if(ft_strnstr(cmd, env->name, ft_strlen(cmd)) != NULL)
			return (env);
		env = env->next;
	}
	return ('\0');
}

