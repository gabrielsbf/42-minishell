/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:11:15 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/18 01:11:17 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_num(t_parse **parser)
{
	t_parse	*temp;
	int		pipe_num;

	pipe_num = 0;
	temp = (*parser);
	while (temp)
	{
		if (temp->special_char != NULL
			&& ft_strcmp(temp->special_char, "|") == 0)
			pipe_num++;
		temp = temp->next;
	}
	return (pipe_num);
}

int	pipe_handler(t_parse **parser)
{
	t_parse	*temp;
	int		fd[2];
	int		last_pipe;

	last_pipe = 0;
	temp = (*parser);
	while (temp->next != NULL)
	{
		if (last_pipe != 0)
			temp->fd_in = last_pipe;
		if (pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		last_pipe = fd[0];
		temp->fd_out = fd[1];
		temp = temp->next;
	}
	temp->fd_in = last_pipe;
	return (0);
}
