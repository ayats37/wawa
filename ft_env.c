/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taya <taya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:51:38 by taya              #+#    #+#             */
/*   Updated: 2025/06/13 10:51:39 by taya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env_list)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
