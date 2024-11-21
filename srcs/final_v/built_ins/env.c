/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:30:31 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_env(t_env **env, t_parse **parser)
{
	t_env	*temp;

	temp = (*env);
	while (temp)
	{
		if (ft_strcmp(temp->name, "?") == 0)
		{
			temp = temp->next;
			continue ;
		}
		ft_putstr_fd(temp->name, (*parser)->fd_out);
		ft_putstr_fd("=", (*parser)->fd_out);
		ft_putendl_fd(temp->value, (*parser)->fd_out);
		temp = temp->next;
	}
}
