/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:31:38 by taya              #+#    #+#             */
/*   Updated: 2025/06/21 23:58:57 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(char *name, char *value, t_env **env_list)
{
	t_env	*current;
	t_env	*new_env;

	current = *env_list;
	while (current)
	{
		if ((strcmp(current->name, name) == 0))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_env = malloc(sizeof(t_env));
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = *env_list;
	*env_list = new_env;
}

char	*get_env_value(char *name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

t_env	*find_env_var(char *name, t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	env_append(char *name, char *value, t_env **env_list)
{
	t_env	*found_var;
	char	*new_value;
	char	*old_value;

	found_var = find_env_var(name, *env_list);
	if (!found_var)
	{
		update_env(name, value, env_list);
		return ;
	}
	old_value = get_env_value(name, *env_list);
	if (old_value)
	{
		new_value = ft_strjoin(old_value, value);
		update_env(name, new_value, env_list);
		free(new_value);
	}
	else
		update_env(name, value, env_list);
}

int	count_env_nodes(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
