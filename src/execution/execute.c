#include "minishell.h"

void	destroy_heredocs_fd(void)
{
	t_commands	*pivot;

	pivot = g_megabash.cmd_list;
	while (pivot)
	{
		if (pivot->redirect && pivot->redirect->type == is_here_doc)
			unlink("./src/heredoc/heredoc_content");
		pivot = pivot->next;
	}
}

void	executing_processes(void)
{
	// print_commands(g_megabash.cmd_list);
	if (g_megabash.pipe == 0)
		execute_single_command();
	else
		execute_multiple_commands();
	destroy_heredocs_fd();
}
