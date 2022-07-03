#include "minishell.h"

void	treat_token_list(void)
{
	t_token	*temp;

	temp = g_megabash.token_list;
	while (temp)
	{
		treat_quote(temp->content);
		temp->content = treat_dollar(temp->content);
		temp = temp->next;
	}
}

void	tokenizer(char *input)
{
	char	**temp;
	int		i;

	i = 1;
	temp = ft_split(input, ' ');
	// free(input);
	if (temp != NULL)
	{
		g_megabash.token_list = token_lst_new(temp[0]);
		while (temp[i])
		{
			token_addback(&g_megabash.token_list, token_lst_new(temp[i]));
			if (temp[i])
				i++;
		}
	}
	free_matrix(temp);
	set_token_type(g_megabash.token_list);
}
