/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:52:57 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

static void	check_quote_process(char *l_read, int iter, int *lock, int *prior)
{
	if ((l_read[iter] == 39
			|| l_read[iter] == 34) && *lock == 0)
	{
		*prior = l_read[iter];
		*lock = 1;
	}
	else if (l_read[iter] == *prior)
	{
		*lock = 0;
		*prior = 0;
	}
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
		check_quote_process(line_read, iter, &lock, &prior);
		iter++;
	}
	if (prior == 0 && (line_read[mem] == 34 || line_read[mem] == 39))
		return (line_read[mem] * 2);
	else
		return (prior);
}

void	join_specific_quote(char **dst, char qt, int is_begin)
{
	char	*c;
	char	*copy;

	copy = ft_strdup(*dst);
	c = ft_calloc(sizeof(char), 2);
	c[0] = qt;
	free_str(dst);
	if (is_begin == 1)
		*dst = join_str_val(c, copy);
	else
		*dst = join_str_val(copy, c);
	free_str(&copy);
	free_str(&c);
}

void	exclude_quotes(char **argument)
{
	char	*copy_text;
	int		i;
	char	flag;

	if (!(*argument))
		return ;
	i = 1;
	flag = (*argument)[0];
	copy_text = NULL;
	if ((*argument)[0] != 39 && (*argument)[0] != 34)
		return ;
	copy_text = ft_strdup((*argument));
	free_str(argument);
	while (copy_text[i] != '\0' && (copy_text[i]) != flag)
		i++;
	(*argument) = ft_substr(copy_text, 1, i - 1);
	free_str(&copy_text);
}
