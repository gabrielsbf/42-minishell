/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:12:20 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*redirect incomplete*/
void	append(t_parse **parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name((*parser)->redir[redir_i]);
	if ((*parser)->fd_out != 1)
		close((*parser)->fd_out);
	(*parser)->fd_out = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	free_str(&file_name);
}
