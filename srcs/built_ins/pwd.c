/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:33:13 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/09 01:33:14 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_parse **parser)
{
	char	cwd[4097];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putendl_fd("PWD ERROR", 2);
		return (1);
	}
	else
		ft_putendl_fd(cwd, (*parser)->fd_out);
	return (0);
}
