/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:44 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/16 00:36:05 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_env{
	char			*name;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

void			environment(char **envp);
char			*get_env_name(char *envp);
struct s_env	*get_env_node(t_env *list, char *name);
char			*get_env_path(char *envp);
void			env_content_to_null(t_env *list, char *name);
void			env_node_delete(t_env *list);
void			print_env(t_env *env);

#endif
