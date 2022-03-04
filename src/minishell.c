#include "minishell.h"



int	main(int argc, char **argv)
{
	t_root	root;
	pid_t	child_pid;
	if (argc < 1)
		exit (1);
	if (argv[0] != ft_strnstr(argv[0], "./minishell", 11))
		exit (1);
	while(1)
	{
		root.input = readline("megabash$ ");
		root.parsed_input = tratar_o_input(root.input);
		child_pid = fork();
		if (child_pid < 0)
			exit(1);
		if (child_pid == 0)
		{
			printf("### Child ###\nCurrent PID: %d\n Child PID: %d\n",
            	getpid(), child_pid);
		}
		else
		{
			waitpid(child_pid, NULL, WNOHANG);
			printf("### Parent ###\nCurrent PID: %d\nChild PID: %d\n",
        		getpid(), child_pid);
		}
	}
}
