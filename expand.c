/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:58:35 by taya              #+#    #+#             */
/*   Updated: 2025/06/22 11:00:11 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_value(char *token, int *i, t_env *env_list)
{
	int		start;
	int		len;
	char	*var_name;
	char	*val;

	start = *i;
	while (token[*i] && (is_alphanumeric(token[*i]) || token[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = strndup(&token[start], len);
	val = get_env_value(var_name, env_list);
	free(var_name);
	if (val)
		return (strdup(val));
	return (strdup(""));
}

char	*expand_dollar_var(char *token, int *i, t_env *env_list,
		int last_exit_status)
{
	if (token[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_exit_status));
	}
	if (token[*i] && (token[*i] == '_' || is_alpha(token[*i])))
		return (get_variable_value(token, i, env_list));
	(*i)++;
	return (strdup("$"));
}

int	append_char_to_result(char **result, char c)
{
	char	*tmp;
	char	*new;

	tmp = char_to_str(c);
	if (!tmp)
		return (0);
	new = str_join_free(*result, tmp);
	free(tmp);
	if (!new)
		return (0);
	*result = new;
	return (1);
}

char	*expand_token(char *token, t_env *env_list, int last_exit_status)
{
	int		i;
	char	*exp;
	char	*result;

	result = strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			exp = expand_dollar_var(token, &i, env_list, last_exit_status);
		}
		else
			exp = char_to_str(token[i++]);
		if (!exp)
			return (free(result), NULL);
		result = str_join_free(result, exp);
		free(exp);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	expand_variables(char **tokens, int last_exit_status, t_env *env_list)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i])
	{
		expanded = expand_token(tokens[i], env_list, last_exit_status);
		free(tokens[i]);
		tokens[i] = expanded;
		i++;
	}
}
