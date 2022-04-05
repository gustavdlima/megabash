#include "minishell.h"

int	is_operator(char *input)
{
	int	i;
	char	**content;

	i = 0;
	content = ft_split(input, ' ');
	while (content[i])
	{
		if (!ft_strncmp(content[i], "|", 2) || !ft_strncmp(content[i], ">", 2)
			|| !ft_strncmp(content[i], "<", 2)
			|| !ft_strncmp(content[i], ">>", 3)
			|| !ft_strncmp(content[i], "<<", 3))
		{
			free_matrix(content);
			return (1);
		}
		i++;
	}
	free_matrix(content);
	return (0);
}

void	create_list(char *input)
{
	g_megabash.cmd = cmd_lst_new();

}

// checar se tem e quantos tem pipes e redirecionamento
// se tem permissao de criar o arquivo nos casos de redirecionamento
// caso nao tenha nada, cria um processo filho e o executa, mas redireciona para a saida padrao (se nao for)

// //

// Quando nao for um comando encontrado pelo ACCESS eh um BUILTIN.

// 1. echo oi

// 2. echo texto | grep "x"

// 3. echo oi << file

// 4. ls >> file
// 5. cat > file

// 6.  < file


// lista:

// cmd -> pra identificar o comando eu uso access ou checo se eh um builtin;
// argumentos -> o que vier depois do comando ate um pipe

// seria interessante separar a linha de comando toda? por exemplo, a cada pipe a gente separa os comandos..
