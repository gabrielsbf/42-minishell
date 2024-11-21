/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:51:41 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	input_elements(char **dst, char *ref, int f_index, int l_index)
{
	char	*temp;

	temp = substr_val(ref, f_index, l_index);
	(*dst) = inject_text(dst, &temp, NULL, NULL);
	free_str(&temp);
}

static void	pre_quote(char *ref, char **dst, int *i, int *start)
{
	char	*temp;
	char	quote;
	int		begin;
	int		sub;

	begin = *i;
	temp = NULL;
	quote = ref[begin];
	while (begin >= 0 && !ft_isspace(ref[begin])
		&& !is_spchar(&ref[begin]))
		begin--;
	if (begin < 0)
		sub = 0;
	else
		sub = begin + 1;
	temp = substr_val(ref, *start, sub);
	*dst = inject_text(dst, &temp, NULL, NULL);
	join_specific_quote(dst, quote, 0);
	free_str(&temp);
	*start = sub;
}

static void	quote_op(char *ref, char **dst, int *f_qt, int *start)
{
	int		begin;
	int		l_qt;
	int		last;
	int		inc;

	inc = ref[*f_qt];
	while ((ref[*f_qt] == 34 || ref[*f_qt] == 39))
	{
		inject_in_op(dst, ref, start, f_qt);
		begin = *f_qt;
		l_qt = get_next_match(ref, *f_qt, ref[(*f_qt)]);
		last = l_qt;
		check_and_setvars(&last, &begin, ref, 1);
		set_positions(ref, &begin, &last, start);
		input_elements(dst, ref, begin, (*f_qt) - 1);
		input_elements(dst, ref, (*f_qt) + 1, l_qt);
		input_elements(dst, ref, l_qt + 1, last);
		check_and_setvars(&last, f_qt, ref, 0);
		set_vars(ref, f_qt, start, last);
	}
	if (inc == 34 || inc == 39)
		join_specific_quote(dst, inc, 0);
}

static void	init_quote_vars(char **l_return, char **t_line, int *i, int *start)
{
	*t_line = NULL;
	*l_return = NULL;
	*i = 0;
	*start = 0;
}

char	*join_quotes(char *line_pre)
{
	char	*line_return;
	char	*line_sub;
	char	*temp_line;
	int		i;
	int		start;

	init_quote_vars(&line_return, &temp_line, &i, &start);
	line_sub = exclude_spaces(line_pre);
	if (necessary_change(line_sub) == 0)
		return (line_sub);
	while (line_sub[i] != '\0')
	{
		if (line_sub[i] == 34 || line_sub[i] == 39)
			pre_quote(line_sub, &line_return, &i, &start);
		quote_op(line_sub, &line_return, &i, &start);
		if (line_sub[i] == '\0')
			break ;
		i++;
	}
	temp_line = substr_val(line_sub, start, i);
	line_return = inject_text(&line_return, &temp_line, NULL, NULL);
	free_str(&line_sub);
	return (line_return);
}
