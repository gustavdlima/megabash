#include "minishell.h"

char	*original_cmd(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(cmd);
	while (i < j)
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				if (cmd[i] == 1)
					cmd[i] = ' ';
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				if (cmd[i] == 1)
					cmd[i] = ' ';
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	*treating_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\0')
			{
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		if (cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\"' && cmd[i] != '\0')
			{
				if (cmd[i] == ' ')
					cmd[i] = 1;
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	**tratar_o_input(char *input)
{
	char	**cmd;
	char	*to_treat;
	int		i;

	// to_treat = malloc((ft_strlen(input)+1) * sizeof(char));
	to_treat = treating_cmd(input);
	cmd = ft_split(to_treat, ' ');
	if (!cmd)
	{
		perror("Failed to process the command");
		exit(1);
	}
	// free(to_treat);
	i = 0;
	while (cmd[i])
	{
		cmd[i] = original_cmd(cmd[i]);
		i++;
	}
	return(cmd);
}

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
			for (int i = 0; root.parsed_input[i]; i++)
			{
				printf("\n\ncmd %d: %s\n", i, root.parsed_input[i]);
			}
		}
		else
		{
			waitpid(child_pid, NULL, WUNTRACED);
			printf("### Parent ###\nCurrent PID: %d\nChild PID: %d\n",
        		getpid(), child_pid);
		}
		free(root.input);
		for (int i = 0; root.parsed_input[i]; i++)
			free(root.parsed_input[i]);
		free(root.parsed_input);
	}
}
