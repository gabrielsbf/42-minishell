/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 00:21:17 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_blank_substr(char *line_read, int memory, int pos)
{
	if (pos > (int)ft_strlen(line_read))
		pos = ft_strlen(line_read);
	if (pos < memory)
		return (-2);
	while (pos >= memory)
	{
		if (!ft_isspace(line_read[pos]) && line_read[pos] != '\0')
			return (0);
		pos--;
	}
	return (1);
}

/*
Validates the quotes on line buffer.

every simple or double quote that starts needs to have a second to end.
.*/

int	test_quote(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] != '\0')
	{
		if ((line_read[i] == 34 || line_read[i] == 39))
			i = get_next_match(line_read, i, line_read[i]);
		if (i == -1)
			return (0);
		i++;
	}
	return (1);
}

int	check_along(char *line_read, int i)
{
	int	back;

	back = i - 1;
	while (back >= 0 && is_spchar(&line_read[back]) > 0)
		back--;
	while (back >= 0 && ft_isspace(line_read[back]))
		back--;
	if (back < 0 && is_spchar(&line_read[i - 1]) == 1)
		return (is_spchar(&line_read[i - 1]));
	while (ft_isspace(line_read[i]) == 1)
		i++;
	if (line_read[i] == '\0')
		return (4);
	else
		return (is_spchar(&line_read[i]));
}
