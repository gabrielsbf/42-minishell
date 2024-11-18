/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:39:58 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/17 22:55:04 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	necessary_change(char *line_sub)
{
	int	i;

	i = 0;
	while (line_sub[i] != '\0')
	{
		if (line_sub[i] == 34 || line_sub[i] == 39)
		{
			i = get_next_match(line_sub, i, line_sub[i]);
			if (!ft_isspace(line_sub[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	set_vars(char *ref, int *i, int *start, int final)
{
	if (final >= (int)ft_strlen(ref))
	{
		*i = ft_strlen(ref);
		*start = *i;
	}
	else
	{
		*i = final;
		if (is_spchar(&ref[(*i)]) > 0)
			*i = *i;
		else if (ref[*i] != '\0' && is_spchar(&ref[(*i) + 1]) > 0)
			(*i) = (*i) + 1;
	}
	*start = *i;
	while (ref[*i] != '\0' && is_spchar(&ref[(*i) + 1]) > 0)
		(*i) = (*i) + 1;
}

void	check_and_setvars(int *final, int *begin, char *ref, int proc)
{
	int	i;

	i = 0;
	if (proc == 1)
	{
		if (*begin > 0
			&& is_spchar(&ref[(*begin) - 1]) == 0)
			(*begin) = (*begin) - 1;
		if (ref[*final] != '\0'
			&& is_spchar(&ref[(*final) + 1]) == 0)
			(*final) = (*final) + 1;
	}
	else if (proc == 0)
	{
		i = get_next_match(ref, *final, ref[(*final)]);
		if (i < 0 && is_quote(ref[(*final)]))
			(*final) = (*final) + 1;
	}
}

void	set_positions(char *ref, int *begin, int *last, int *start)
{
	while (*begin >= 0 && *begin > *start
		&& !ft_isspace(ref[*begin]) && !is_quote(ref[*begin])
		&& is_spchar(&ref[*begin]) == 0)
		(*begin)--;
	if (*begin == -1)
		(*begin)++;
	while (ref[*last] != '\0' && !ft_isspace(ref[*last])
		&& !is_quote(ref[*last]) && is_spchar(&ref[*last]) == 0)
		(*last)++;
}
