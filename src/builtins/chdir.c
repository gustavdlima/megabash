#include "minishell.h"

static void new_pwd_env(void)
{
	char	*directory;
	t_env	*env_node;

	directory = getcwd(NULL, 0);
	env_node = get_env_node(g_megabash.env, "PWD");
	if (env_node == NULL)
		env_addback(&g_megabash.env, env_lst_new("PWD", directory));
	else
		env_node->content = ft_strdup(directory);
}

static void	new_oldpwd_env(void)
{
	char	*directory;
	t_env	*env_node;

	directory = getcwd(NULL, 0);
	env_node = get_env_node(g_megabash.env, "OLDPWD");
	if (env_node == NULL)
		env_addback(&g_megabash.env, env_lst_new("OLDPWD", directory));
	else
		env_node->content = ft_strdup(directory);
}

static void home_execute(void)
{
	t_env	*env_node;

	env_node = get_env_node(g_megabash.env, "HOME");
	if (env_node == NULL)
	{
		ft_putendl_fd("megabash: cd: HOME not set", 2);
		return ;
	}
	else
	{
		new_oldpwd_env();
		chdir(env_node->content);
		new_pwd_env();
	}
}

static void	dash_execute(void)
{
	char	*directory;
	t_env	*env_node;

	env_node = get_env_node(g_megabash.env, "OLDPWD");
	directory = ft_strdup(env_node->content);
	if (env_node == NULL)
	{
		ft_putendl_fd("megabash: cd: OLDPWD not set", 2);
		return ;
	}
	else
	{
		new_oldpwd_env();
		chdir(directory);
		new_pwd_env();
	}
}

void	cd(char **matrix)
{
	if (matrix_size(matrix) > 1)
	{
		ft_putendl_fd("megabash: cd: too many arguments", 2);
		g_megabash.exit_status = 1;
		exit(1);
	}
	if(matrix_size(matrix) == 0 || !ft_strncmp(g_megabash.cmd_list->content[1], "~", 2))
		home_execute();
	else if(!ft_strncmp(g_megabash.cmd_list->content[1], "-", 2))
		dash_execute();
	else
	{
		new_oldpwd_env();
		if(chdir(matrix[1]))
		{
			ft_putstr_fd("megabash: cd:", 2);
			ft_putstr_fd(matrix[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_megabash.exit_status = 1;
			exit(1);
		}
		new_pwd_env();
	}
}
