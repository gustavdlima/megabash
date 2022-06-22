#include "minishell.h"

static void signint(int signum)
{
  (void)signum;
  printf("\n");
  rl_replace_line("", 0);
  rl_on_new_line();
  rl_redisplay();
  g_megabash.exit_status = 130;
}

void	signal_handler(void)
{
	signal(SIGINT, signint);
	signal(SIGQUIT, SIG_IGN);
}

// ◦ ctrl-C displays a new prompt on a new line.

// ◦ ctrl-D exits the shell.

// ◦ ctrl-\ does nothing.
