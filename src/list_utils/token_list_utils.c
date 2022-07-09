#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("%s\n", token->content);
		token = token->next;
	}
}

int	token_pipe_checker(t_token *token)
{
	t_token	*list;

	list = token;
	while (list)
	{
		if (list->type == is_pipe)
			return (true);
		list = list->next;
	}
	return (false);
}

static t_token	*cut_node(t_token *list)
{
	list->next->prev = list->prev;
	list->prev->next = list->next;
	return (list);
}

t_token	*token_content_to_hell(t_token *list, char *name, char *true_name)
{
	t_token	*temp;

	while (list)
	{
		if (ft_new_strncmp(name, list->content))
		{
			temp = list;
			if (list->next)
				list = cut_node(list);
			else
				list->prev->next = NULL;
			break ;
		}
		list = list->next;
	}
	while (list)
	{
		if (ft_new_strncmp(true_name, list->content))
		{
			free_token(temp);
			return (list);
		}
		list = list->prev;
	}
	return (list);
}

void	free_token(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token;
		token = token->next;
		free(temp->content);
		free(temp);
	}
}
