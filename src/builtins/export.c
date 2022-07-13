#include "minishell.h"

static int	print_export_error(char *name, int i)
{
	i++;
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(name, 2);
	error_message("': not a valid identifier", 1);
	return (i);
}

static void	export_new_node(char *name, char *content)
{
	env_addback(&g_megabash.env, env_lst_new(name, content));
	free(name);
	free(content);
}

static int	export_execute(char *name, char *content, char **command, int i)
{
	t_env	*node;

	node = g_megabash.env;
	if (!ft_strchr(command[i], '='))
		return (i + 1);
	name = get_env_name(command[i]);
	if (!is_alphabetic(name))
	{
		free(name);
		return (print_export_error(command[i], i));
	}
	content = get_env_path(command[i]);
	node = get_env_node(g_megabash.env, name);
	if (!node)
		export_new_node(name, content);
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
		if (ft_new_strncmp("=", command[i])
			|| command[i][0] == '=')
		{
			i = print_export_error(command[i], i);
			continue;
		}
		if ((!ft_strchr(command[i], '=')) && (!is_alphabetic(command[i])))
		{
			i = print_export_error(command[i], i);
			continue ;
		}
		i = export_execute(name, content, command, i);
		continue ;
	}
}
