/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:11:54 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/06/13 11:14:40 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *value, char quote, int has_space)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	else
	{
		token->value = ft_strdup(value);
		token->next = NULL;
	}
	if (quote == '\'')
		token->type = 3;
	else if (quote == '"')
		token->type = 4;
	else
		token->type = 0;
	token->has_space = has_space;
	token->fd = -1;
	return (token);
}

t_type	token_type(t_token *token)
{
	if (token->type == 3)
		return (SINGLE_QUOTE);
	else if (token->type == 4)
		return (DOUBLE_QUOTE);
	else if (strcmp(token->value, "||") == 0)
		return (OR);
	else if (strcmp(token->value, "&&") == 0)
		return (AND);
	else if (strcmp(token->value, "|") == 0)
		return (PIPE);
	else if (strcmp(token->value, ">>") == 0)
		return (APPEND);
	else if (strcmp(token->value, "<<") == 0)
		return (HEREDOC);
	else if (strcmp(token->value, "<") == 0)
		return (REDIR_IN);
	else if (strcmp(token->value, ">") == 0)
		return (REDIR_OUT);
	else if (strcmp(token->value, "(") == 0)
		return (OPEN_PAREN);
	else if (strcmp(token->value, ")") == 0)
		return (CLOSE_PAREN);
	else
		return (CMD);
}

void	append_token(t_token **head, t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (!token)
		return ;
	if (!*head)
	{
		*head = token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}

void	merge_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*to_delete;
	char	*merged_value;

	// t_token	*tmp;
	to_delete = NULL;
	// tmp = NULL;
	current = *tokens;
	while (current != NULL && current->next != NULL)
	{
		if (current->has_space == 0 && ((current->type == SINGLE_QUOTE
					|| current->type == DOUBLE_QUOTE || current->type == 1)
				&& (current->next->type == SINGLE_QUOTE
					|| current->next->type == DOUBLE_QUOTE
					|| current->next->type == 1)))
		{
			merged_value = ft_strjoin(current->value, current->next->value);
			current->value = merged_value;
			if (current->type == CMD || current->next->type == CMD)
				current->type = CMD;
			current->has_space = current->next->has_space;
			to_delete = current->next;
			current->next = to_delete->next;
		}
		else
		{
			// tmp = current;
			current = current->next;
		}
	}
}
