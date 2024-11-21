/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:11:32 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redirect_in(t_env **env, t_parse **parser, int redir_i)
{
	char	*file_name;
	int		redir_in;

	file_name = get_redir_name((*parser)->redir[redir_i]);
	redir_in = open(file_name, O_RDONLY);
	if (redir_in == -1)
	{
		(*parser)->status = 1;
		update_env_status(env, 1);
		ft_putendl_fd("input redirect: ERROR", 2);
		free_str(&file_name);
		return ;
	}
	if ((*parser)->fd_hdoc != 0)
		close((*parser)->fd_hdoc);
	(*parser)->fd_hdoc = redir_in;
	free_str(&file_name);
}
