#include "minishell.h"

// static void	treat_parse_list(void)
// {
// 	t_commands	*temp;
// 	int			i;

// 	temp = g_megabash.cmd_list;
// 	i = 0;
// 	while (temp)
// 	{
// 		while (temp->content[i])
// 		{
// 			temp->content[i] = no_quotes(temp->content[i]);
// 			reverse_input_chars(temp->content[i]);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// }

// t_commands	*take_command(t_token *token, t_commands *command)
// {
	
// }

// t_token	*to_null_or_pipe(t_token *token)
// {
// 	while (token)
// 	{
// 		if (token->next == NULL || token->next->type == IS_PIPE)
// 			break ;
// 		token = token->next;
// 	}
// 	return (token);
// }

// void	parsing(void)
// {
// 	t_token		*token;
// 	t_commands	*command;

// 	token = g_megabash.token_list;
// 	command = NULL;
// 	while (token)
// 	{

// 	}
//     // print_commands(command);
// 	// treat_parse_list();
// }

/*
    Em cada nó da lista de comando, vão ter esses momentos:

    ps: a ordem dos comandos vai depender do redirecionamento <-

    1. definir o cmd principal do nó;
        input: ls -l | cat arquivo          (comando principal ls e cat);
    2. definir o tipo do comando
        input: echo "oi"                    (type = BUILTIN)
    2. juntar o input inteiro até um operador;
        input: ls -l | cat arquivo          (conteudo vai ser ls -l e cat arquivo);
    3. se o token for de redirect ou here-doc, vou colocar

*/

Existem comandos simples e comandos complexos. Comandos simples não tem pipe, ja complexos tem  

 o Word pode ser reduzido para cmd se aparecer no início, arg_list se aparecer depois de um comando, 
 file se aparecer depois de um redirecionamento, então a sentença é analisada de acordo com a gramática,