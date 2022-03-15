#include "minishell.h"

void	find_redirections(t_root *root)
{
	int	i;

	i= 0;
	while (root->input[i])
	{
		if (root->input[i] == '<')
		{
			i++;
			if (root->input[i] == '<')
				printf("should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!\n");
			else
				printf("redirect_input(root)\n");
			return ;
		}
		if (root->input[i] == '>')
		{
			i++;
			if (root->input[i] == '>')
				printf("should redirect output in append mode\n");
			else
				printf("redirect_output(root)\n");
			return ;
		}
		i++;
	}
	input_treat(root);
}
