#include "minishell.h"

static void	print_export_error(char *name)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(name);
}

static int	export_execute(char *name, char *content, t_env *node, char **command, int i)
{
	if (!ft_strchr(command[i], '='))
	{
		i++;
		return (i);
	}
	if  (is_alphabetic(command[i]))
	{
		print_export_error(command[i]);
		i++;
		return (i);
	}
	free(name);
	free(content);
	name = get_env_name(command[i]);
	content = get_env_path(command[i]);
	node = get_env_node(g_megabash.env, name);
	if (!node)
		env_addback(&g_megabash.env, env_lst_new(name, content));
	else
	{
		env_content_to_null(node, name);
		node->content = ft_strdup(content);
	}
	i++;
	return (i);
}

void	export(char **command)
{
	int		i;
	char	*name;
	char	*content;
	t_env	*node;

	node = g_megabash.env;
	i = 1;
	while (command[i])
	{
		name = ft_strdup("");
		content = ft_strdup("");
		i = export_execute(name, content, node, command, i);
		continue ;
		// if (!ft_strchr(command[i], '='))
		// {
		// 	i++;
		// 	continue ;
		// }
		// if (is_alphabetic(command[i]))
		// {
		// 	print_export_error(command[i]);
		// 	i++;
		// 	continue ;
		// }
		// name = get_env_name(command[i]);
		// content = get_env_path(command[i]);
		// node = get_env_node(g_megabash.env, name);
		// if (!node)
		// 	env_addback(&g_megabash.env, env_lst_new(name, content));
		// else
		// {
		// 	env_content_to_null(node, name);
		// 	node->content = ft_strdup(content);
		// }
		// i++;
	}
}

// se nao vier com =, so retorno a funcao