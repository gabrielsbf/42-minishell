/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:28:44 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/17 23:33:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*(finished) Count the number of char * present on the vector.*/
int	count_arr_nb(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}

int	jump_special_char(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] != '\0'
		&& is_spchar(line_read + i))
		i++;
	return (i);
}

void	make_space_rm(char **l_return, char *l_sub, int *i, int *start)
{
	char	*temp_line;

	temp_line = NULL;
	if (*i != *start)
	{
		if (l_sub[*i] == '\0')
			temp_line = substr_val(l_sub, *start, *i);
		else
			temp_line = substr_val(l_sub, *start, (*i) + 1);
		(*l_return) = inject_text(l_return, &temp_line, NULL, NULL);
		*start = *i;
	}
}

char	*exclude_spaces(char *line_sub)
{
	char	*line_return;
	char	*temp_line;
	int		i;
	int		start;

	i = 0;
	start = 0;
	temp_line = NULL;
	line_return = NULL;
	while (line_sub[i] != '\0')
	{
		while (line_sub[i] != '\0' && (!ft_isspace(line_sub[i])
				|| is_btw_qts(line_sub, i)))
			i++;
		make_space_rm(&line_return, line_sub, &i, &start);
		if (line_sub[i] == '\0')
			break ;
		i++;
		start++;
	}
	if (i != start)
		temp_line = substr_val(line_sub, start, i);
	line_return = inject_text(&line_return, &temp_line, NULL, NULL);
	return (line_return);
}
