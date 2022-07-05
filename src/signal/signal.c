#include "minishell.h"

static void	signint(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// static void	signint_heredoc(int signum)
// {
// 	(void)signum;
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	update_exit_status_and_exit(130);
// }

// static void	sign_heredoc(int signum)
// {
// 	(void)signum;
// 	printf("\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	update_exit_status_and_exit(130);
// }

void	signal_handler_heredoc(int condition)
{
	if (condition == true)
	{
		signal(SIGINT, signint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (condition == false)
	{
		signal(SIGINT, signint);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	signal_handler(void)
{
	signal(SIGINT, signint);
	signal(SIGQUIT, SIG_IGN);
}

// ◦ ctrl-C displays a new prompt on a new line.

// ◦ ctrl-D exits the shell.

// ◦ ctrl-\ does nothing.
