/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:11:32 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/18 22:00:13 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_in(t_env **env, t_parse **parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name((*parser)->redir[redir_i]);
	if ((*parser)->fd_in != 0)
		close((*parser)->fd_in);
	(*parser)->fd_in = open(file_name, O_RDONLY);
	if ((*parser)->fd_in == -1)
	{
		(*parser)->fd_in = 0;
		(*parser)->status = 1;
		update_env_status(env, 1);
		ft_putendl_fd("input redirect: ERROR", 2);
	}
	free_str(&file_name);
}
