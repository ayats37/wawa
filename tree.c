/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:02 by taya              #+#    #+#             */
/*   Updated: 2025/06/22 17:00:18 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_tree(t_tree *node, t_env **envlist, int last_status)
{
	int	status;

	status = 0;
	if (!node)
		return (1);
	if (node->type == PIPE)
		return (execute_pipe(node, envlist, last_status));
	else if (node->type == CMD || node->type == DOUBLE_QUOTE)
	{
		write(1, "aya\n", 4);
		expand_variables(node->cmd, last_status, *envlist);
		if (is_builtin(node->cmd[0]))
			return (execute_builtin(node, envlist));
		else
			return (execute_cmd(node->cmd, *envlist, node));
	}
	else if (node->type == AND || node->type == OR)
	{
		status = execute_tree(node->left, envlist, last_status);
		if (node->type == AND && status == 0)
			return (execute_tree(node->right, envlist, status));
		if (node->type == OR && status != 0)
			return (execute_tree(node->right, envlist, status));
		return (status);
	}
	return (1);
}
