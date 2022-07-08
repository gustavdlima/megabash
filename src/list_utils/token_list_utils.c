#include "minishell.h"

void	print_token(t_token *token)
{
	if (!token)
		return ;
	// printf("\nToken content: ------------\n");
	while (token)
	{
		printf("%s\n", token->content);
		token = token->next;
	}
	// printf("---------------------------\n");
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

t_token	*token_lst_new(char *content)
{
	t_token	*element;

	element = malloc(sizeof(t_token));
	if (element)
	{
		element->type = 0;
		element->content = ft_strdup(content);
		element->next = NULL;
		element->prev = NULL;
		return (element);
	}
	return (0);
}

void	token_addback(t_token **lst, t_token *new)
{
	t_token	*last_node;

	if (*lst)
	{
		last_node = token_last_node(*lst);
		last_node->next = new;
		new->prev = last_node;
	}
	else
		*lst = new;
}

t_token	*token_last_node(t_token *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

struct s_token	*get_token_node(t_token *list, char *name)
{
	while (list)
	{
		if (ft_new_strncmp(list->content, name) == true)
			return (list);
		list = list->next;
	}
	return (NULL);
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
			{
				list->next->prev = list->prev;
				list->prev->next = list->next;
			}
			else
			{
				list->prev->next = NULL;
			}
			break ;
		}
		list = list->next;
	}
	while (list)
	{
		if (ft_new_strncmp(true_name, list->content))
		{
			free(temp->content);
			free(temp);
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
