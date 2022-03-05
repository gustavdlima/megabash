#include "minishell.h"

char	*command_line(t_root *root)
{
	root->input = readline("megabash$ ");
	add_history(root->input);
	return(root->input);
}
