/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:54:20 by taya              #+#    #+#             */
/*   Updated: 2025/06/22 01:21:20 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_tree(t_tree *node)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->cmd)
	{
		while (node->cmd[i])
		{
			free(node->cmd[i]);
			i++;
		}
		free(node->cmd);
	}
	if (node->redir)
		free_tokens(node->redir);
	free(node);
}

void	free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer);
}

void	free_resources(char *input, t_lexer *lexer, t_token *token_list,
	t_tree *node)
{
	if (input)
		free(input);
	if (lexer)
		free_lexer(lexer);
	if (token_list)
		free_tokens(token_list);
	if (node)
		free_tree(node);
}
