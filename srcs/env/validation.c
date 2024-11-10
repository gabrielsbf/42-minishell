/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:45:39 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/09 01:46:24 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_name_in_env(t_env **envs, char *name)
{
	t_env	*swap;

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
