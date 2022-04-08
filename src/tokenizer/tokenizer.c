#include "minishell.h"

void	treat_token_list(void)
{
	t_token *temp;

	printf("3.0. check_input\n");
	check_input();
	temp = g_megabash.token_list;
	print_token(temp);
	while (temp)
	{
		treat_quote(temp->content);
		temp->content = treat_dollar(temp->content);
		temp->content = no_quotes(temp->content);
		reverse_input_chars(temp->content);
		temp = temp->next;
	}
}

void	tokenizer (char *input)
{
	int	i;
	char **temp;

	// separar o redirect do oi nesse caso -> echo oi>>
	i = 1;
	temp = ft_split(input, ' ');
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
}
