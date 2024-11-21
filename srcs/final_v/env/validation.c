/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:45:39 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_name_in_env(t_env **envs, char *name)
{
	t_env	*swap;

	if (!name)
		return (NULL);
	swap = (*envs);
	while (swap != NULL)
	{
		if (ft_strncmp(swap->name, name, ft_strlen(name) + 1) == 0)
			break ;
		swap = swap->next;
	}
	if (swap == NULL)
		return (NULL);
	return (swap->value);
}

int	is_env_available(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}
