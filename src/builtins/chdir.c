#include "minishell.h"

static void	save_oldpwd(void)
{
	char	*directory;
	t_env	*env_node;

	directory = getcwd(NULL, 0);
	env_node = get_env_node(g_megabash.env, "OLDPWD");
	env_node->content = ft_strdup(directory);
	print_env(g_megabash.env);
}

void	cd(char **matrix)
{
	save_oldpwd();
	chdir(matrix[1]);
}


// funcao para pegar o diretorio atual e salvar na env pwd
// mudar o diretorio
// funcao para pegar o diretorio antigo e salvar na env old_pwd
// cd -, cd ~, cd 
