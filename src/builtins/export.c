#include "minishell.h"

static int	i_plus_plus(int i)
{
	i++;
	return (i);
}

static int	print_export_error(char *name, int i)
{
	i++;
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (i);
}

static int	export_execute(char *name, char *content, char **command, int i)
{
	t_env	*node;

	node = g_megabash.env;
	if (!ft_strchr(command[i], '='))
		return (i_plus_plus(i));
	if (is_alphabetic(command[i]))
		return (print_export_error(command[i], i));
	name = get_env_name(command[i]);
	content = get_env_path(command[i]);
	node = get_env_node(g_megabash.env, name);
	if (!node)
	{
		env_addback(&g_megabash.env, env_lst_new(name, content));
		free(name);
		free(content);
	}
	else
	{
		env_content_to_null(node, name);
		free(node->content);
		free(name);
		node->content = content;
	}
	i++;
	return (i);
}

void	export(char **command)
{
	int		i;
	char	*name;
	char	*content;

	i = 1;
	name = NULL;
	content = NULL;
	while (command[i])
	{
		i = export_execute(name, content, command, i);
		continue ;
	}
}
