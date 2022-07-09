#include "minishell.h"

static void	signint(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_megabash.exit_status = 130;
}

static void	signint_doc(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	free_env(g_megabash.env);
	g_megabash.exit_status = 1;
	free(g_megabash.last_input);
	free_commands(g_megabash.cmd_list);
	// free_env(g_megabash.env);
	exit(130);
}

void	signal_handler_heredoc(void)
{
	signal(SIGINT, signint_doc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(void)
{
	signal(SIGINT, signint);
	signal(SIGQUIT, SIG_IGN);
}

// ◦ ctrl-C displays a new prompt on a new line.

// ◦ ctrl-D exits the shell.

// ◦ ctrl-\ does nothing.
