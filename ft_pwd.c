/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:49 by taya              #+#    #+#             */
/*   Updated: 2025/06/22 12:02:11 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_vars(char *oldpwd, t_env *envlist)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	update_env("OLDPWD", oldpwd, &envlist);
	update_env("PWD", cwd, &envlist);
	free(cwd);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: pwd"), 1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
