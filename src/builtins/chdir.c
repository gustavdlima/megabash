#include "minishell.h"

// ele volta para o diretorio anterior atraves da env oldpwd
// pegar o conteudo da env old_pwd e mandar para chdir

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

static void	dash_execute(void)
{
	char	*directory;
	t_env	*env_node;

	env_node = get_env_node(g_megabash.env, "OLDPWD");
	directory = ft_strdup(env_node->content);
	if (env_node == NULL)
		return ;
	else
	{
		new_oldpwd_env();
		chdir(directory);
		new_pwd_env();
	}
}

void	cd(char **matrix)
{

	if(!ft_strncmp(g_megabash.cmd_list->content[1], "-", 2))
	{
		dash_execute();
	}
	else
	{
		new_oldpwd_env();
		chdir(matrix[1]);
		new_pwd_env();
	}
}


// funcao para pegar o diretorio atual e salvar na env pwd
// mudar o diretorio
// funcao para pegar o diretorio antigo e salvar na env old_pwd
// cd -, cd ~, cd 
