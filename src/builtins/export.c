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
	error_message("': not a valid identifier", 1);
	return (i);
}

static int	export_execute(char *name, char *content, char **command, int i)
{
	t_env	*node;

	node = g_megabash.env;
	if (!ft_strchr(command[i], '='))
		return (i_plus_plus(i));
	name = get_env_name(command[i]);
	if (!is_alphabetic(name))
	{
		dprintf(2, "%s\n", name);
		dprintf(2, "aaaaaaaa\n");
		free(name);
		return (print_export_error(command[i], i));
	}
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
		if ((!ft_strchr(command[i], '=')) && (!is_alphabetic(command[i])))
		{
			dprintf(2, "pq to caindo aqui se tenho igual? kk\n");
			i = print_export_error(command[i], i);
			continue ;
		}
		i = export_execute(name, content, command, i);
		continue ;
	}
}
