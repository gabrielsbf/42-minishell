/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:13:10 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_redir_name(char	*redir)
{
	int		i;
	int		file_i;
	char	*file_name;

	file_i = 0;
	i = 0;
	while (redir[i] != '\0')
	{
		if (redir[i] != '<' && redir[i] != '>'
			&& (redir[i] != ' ' || is_btw_qts(redir, i) > 0))
			file_i++;
		i++;
	}
	file_name = ft_calloc(sizeof(char), file_i + 1);
	i = 0;
	file_i = -1;
	while (redir[i] != '\0')
	{
		if (redir[i] != '<' && redir[i] != '>'
			&& (redir[i] != ' ' || is_btw_qts(redir, i) > 0))
			file_name[++file_i] = redir[i];
		i++;
	}
	exclude_quotes(&file_name);
	return (file_name);
}

void	redirect(t_parse **parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name((*parser)->redir[redir_i]);
	if ((*parser)->fd_out != 1)
		close((*parser)->fd_out);
	(*parser)->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	free_str(&file_name);
}
