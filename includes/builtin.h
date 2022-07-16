/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalves <gusalves@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:05:41 by gusalves          #+#    #+#             */
/*   Updated: 2022/07/15 21:05:42 by gusalves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

void	builtin_exit(char **matrix);
void	export(char **command);
void	unset(char **command);
void	pwd(char **command);
void	free_unset(t_env *list);
void	cd(char **matrix);
void	new_pwd_env(void);
void	new_oldpwd_env(void);
void	builtin_env(char **matrix);
void	echo(char **matrix);
int		is_numeric(char *string);

#endif
