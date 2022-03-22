#include "minishell.h"

void	input_treat(void)
{
	int	cmd_size;
	int	i;

	i = 0;
	cmd_size = ft_strlen(g_megabash.input->input);
	g_megabash.cmd->content = tokenizer(g_megabash.input->input, cmd_size);
	while (g_megabash.cmd->content[i])
	{
		g_megabash.cmd->content[i] = metacharacters_treat(g_megabash.cmd->content[i]);
		g_megabash.cmd->content[i] = no_quotes(g_megabash.cmd->content[i]);
		printf("%s\n", g_megabash.cmd->content[i]);
		i++;
	}
}
