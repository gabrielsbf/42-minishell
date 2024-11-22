/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:54:08 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/22 17:54:11 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	throw_error(int status)
{
	if (status == 2)
		ft_putendl_fd("invalid syntax or argument: ERROR", 2);
	if (status == 127)
		ft_putendl_fd("command not found: ERROR", 2);
}
