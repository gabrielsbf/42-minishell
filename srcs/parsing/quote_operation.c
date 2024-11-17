/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:51:41 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/16 23:37:33 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	pre_quote(char *ref, char **dst, int *i, int *start)
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

void	quote_op(char *ref, char **dst, int *f_qt, int *start)
{
	int		begin;
	int		l_qt;
	int		last;
	char	*temp;
	int		inc;

	inc = ref[*f_qt];
	while ((ref[*f_qt] == 34 || ref[*f_qt] == 39))
	{
		inject_in_op(dst, ref, start, f_qt);
		temp = NULL;
		begin = *f_qt;
		l_qt = get_next_match(ref, *f_qt, ref[(*f_qt)]);
		last = l_qt;
		check_and_setvars(&last, &begin, ref, 1);
		while (begin >= 0 && begin > *start
			&& !ft_isspace(ref[begin]) && !is_quote(ref[begin])
			&& is_spchar(&ref[begin]) == 0)
			begin--;
		if (begin == -1)
			begin++;
		while (ref[last] != '\0' && !ft_isspace(ref[last])
			&& !is_quote(ref[last]) && is_spchar(&ref[last]) == 0)
			last++;
		temp = substr_val(ref, begin, (*f_qt) - 1);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		temp = substr_val(ref, (*f_qt) + 1, l_qt);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		temp = substr_val(ref, l_qt + 1, last);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		check_and_setvars(&last, f_qt, ref, 0);
		set_vars(ref, f_qt, start, last);
	}
	if (inc == 34 || inc == 39)
		join_specific_quote(dst, inc, 0);
}

char	*join_quotes(char *line_pre)
{
	char	*line_return;
	char	*line_sub;
	char	*temp_line;
	int		i;
	int		start;

	temp_line = NULL;
	line_return = NULL;
	line_sub = exclude_spaces(line_pre);
	i = 0;
	start = 0;
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
