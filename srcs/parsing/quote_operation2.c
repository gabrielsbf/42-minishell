/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_operation2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:52:57 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/16 23:54:30 by gabrfern         ###   ########.fr       */
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

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

/*
If
RETURNS:
* either 34 or 39 which means what quote the char is between
* either 68(34 * 2) or 78(39 * 2) which means that the char is quote and
* 0 if it's not between quotes
*/
int	is_btw_qts(char *line_read, int mem)
{
	int	iter;
	int	prior;
	int	lock;

	iter = 0;
	prior = 0;
	lock = 0;
	while (iter <= mem)
	{
		if ((line_read[iter] == 39
				|| line_read[iter] == 34) && lock == 0)
		{
			prior = line_read[iter];
			lock = 1;
		}
		else if (line_read[iter] == prior)
		{
			lock = 0;
			prior = 0;
		}
		iter++;
	}
	if (prior == 0 && (line_read[mem] == 34 || line_read[mem] == 39))
		return (line_read[mem] * 2);
	else
		return (prior);
}
