#include "minishell.h"

static void	prompt_loop(t_commands *command_list)
{
	char	*read;
	char	*arraydoc;

	arraydoc = ft_strdup("");
	while (1)
	{
		read = readline("> ");
		if (command_list->redirect->type == is_here_doc)
			if (!ft_strncmp(command_list->redirect->content, read, ft_strlen(read)))
				break ;
		arraydoc = ft_strjoin(arraydoc, "\n");
		arraydoc = ft_strjoin(arraydoc, read);
		free(read);
	}
}

void	heredoc(t_commands *command_list)
{
	prompt_loop(command_list);
	return ;
}

//     um loop infinito
//     ja consigo parar se for a palavra chave
//     ja tenho tudo concatenado

// tenho que abrir um prompt usando readline ou read
// ao escrever, tenho que continuar abrindo prompt e ir guardando ate
// escrever a palavra-chave 

// caso mande varios heredocs, o ultimo eh que vai quitar..

// eh basicamente um loop de readline onde guarda e printa o conteudo colocado
// e espera a palavra-chave do readline ou um signal de ctrl + D ou ctrl + C
// ctrl c cancela a execucao
// ctrl d interrompe abruptamente e salva o que foi feito ate o momento

// usar fork pra poder abrir uma readline nova