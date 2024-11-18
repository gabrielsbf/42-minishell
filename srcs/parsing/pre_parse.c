/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:26:39 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/16 23:24:01 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
make a validation on a stretch of a
string to see if have validation special chars
special chars are:
'<', '>' and '|'

the '>' chars can be proceeded by one more char of the same:
* >>
* <<
return codes:
returns (1): |
returns (2): > or <
returns (3): >> or <<

if results to 0 it means it's not a special char
*/

int	is_spchar(char *stretch)
{
	if (stretch[0] == '\0')
		return (0);
	if ((stretch[0] == '>' || stretch[0] == '<') && stretch[0] == stretch[1])
		return (3);
	if (stretch[0] == '>' || stretch[0] == '<')
		return (2);
	if (stretch[0] == '|')
		return (1);
	return (0);
}

int	pipe_char_pos(char *line_sub)
{
	int	i;

	i = jump_special_char(line_sub);
	while (line_sub[i] != '\0')
	{
		if (is_spchar(&line_sub[i]) == 1
			&& !is_btw_qts(line_sub, i))
			return (i++);
		i++;
	}
	return (i);
}

int	num_of_pipes(char *line_read)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!line_read)
		return (0);
	while (line_read[i] != '\0')
	{
		if (is_spchar(&line_read[i]) == 1)
			count++;
		i++;
	}
	return (count);
}

char	*separate_line_read(char *line_sub)
{
	int	index;

	index = pipe_char_pos(line_sub);
	if (line_sub[index] == '\0')
		return (ft_substr(line_sub, 0, index));
	return (ft_substr(line_sub, 0, index + 1));
}

int	def_special_char(char *stretch)
{
	if ((stretch[0] == '>' || stretch[0] == '<') && stretch[0] == stretch[1])
		return ((stretch[0]) * 2);
	if (stretch[0] == '>' || stretch[0] == '<')
		return (stretch[0]);
	if (stretch[0] == '|')
		return (stretch[0]);
	return (0);
}
