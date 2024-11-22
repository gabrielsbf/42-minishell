/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 01:22:40 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/20 01:24:37 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	throw_error(int status)
{
	if (status == 2)
		ft_putendl_fd("invalid syntax or argument: ERROR", 2);
	if (status == 127)
		ft_putendl_fd("command not found: ERROR", 2);
}
