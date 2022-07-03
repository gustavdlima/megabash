#include "minishell.h"

void	quit_megabash(void)
{
	// //funcoes para dar free
	// free_env(g_megabash.env);
	free_token(g_megabash.token_list);
	free_commands(g_megabash.cmd_list);
	rl_clear_history();
	exit(g_megabash.exit_status);
}


// tenho que garantir que o exit_code esteja sendo gravado em g_megabash.exit_code durante o 
// andamento do programa e prevendo os casos que vai ser 0, 127, 126 ou > 0
// a funcao de exit e free sao necessarias pra casos especificos que eh basicamente
//  quando o shell vai ser finalizado.

// 0 exit status has succeeded.
// If a command is not found, the child process created to execute it returns a status of 127.
// If a command is found but is not executable, the return status is 126. 
// If a command fails because of an error during expansion or redirection, the exit status is greater than zero. 
// All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure, 
// so they may be used by the conditional and list constructs. 
// All builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments. 