#include "minishell.h"

void	free_unset(t_env *list)
{
	free(list->name);
	free(list->content);
	free(list);
}

static int	print_unset_error(char *name, int i)
{
	i++;
	ft_putstr_fd("unset: '", 2);
	ft_putstr_fd(name, 2);
	error_message("': not a valid identifier", 1);
	return (i);
}


void	unset(char **command)
{
	t_env	*temp;
	t_env	*env_test;
	int		i;

	env_test = g_megabash.env;
	i = 1;
	if (command && !command[1])
		return ;
	while (command[i])
	{
		if (!is_alphabetic(command[i]))
		{
			i = print_unset_error(command[i], i);
			continue ;
		}
		temp = get_env_node(env_test, command[i]);
		if (temp)
			env_node_delete(temp);
		i++;
	}
}
