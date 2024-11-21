/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:32:40 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
(finished) Function is called when a char that
normally the user wants to target is encountered,
it then get the index of the char c encountered at
the string(line_read) the position argument set
where is the index of the string
that you want to begin.
The return is the absolute index of the position
of the encountered char
*/
int	get_next_match(char *line_read, int position, char c)
{
	position++;
	if (position > (int)ft_strlen(line_read))
		return (-1);
	while (line_read[position] != '\0' && line_read[position] != c)
		position++;
	if (line_read[position] != c)
		return (-1);
	return (position);
}

/*Verify if it is necessary to make a change on the quotes part.*/

char	*join_str_val(char *init, char *end)
{
	if (init == NULL && end == NULL)
		return (NULL);
	else if (init == NULL)
		return (ft_strdup(end));
	else if (end == NULL)
		return (ft_strdup(init));
	else
		return (ft_strjoin(init, end));
}

char	*inject_text(char **start, char **end, char *prefix, char *sufix)
{
	char	*result;
	char	*end_complete;
	char	*pre_complete;

	result = NULL;
	pre_complete = join_str_val(*start, prefix);
	end_complete = join_str_val(*end, sufix);
	result = join_str_val(pre_complete, end_complete);
	free_str(&pre_complete);
	free_str(&end_complete);
	free_str(start);
	free_str(end);
	*end = NULL;
	*start = NULL;
	pre_complete = NULL;
	end_complete = NULL;
	return (result);
}

char	*substr_val(char *s, int start, int final)
{
	if (start >= final)
		return (NULL);
	return (ft_substr(s, start, final - start));
}

void	inject_in_op(char **dst, char *ref, int *start, int *f_qt)
{
	char	*temp;

	temp = NULL;
	if (*dst == NULL)
		*dst = substr_val(ref, *start, *f_qt);
	else
	{
		temp = substr_val(ref, *start, *f_qt);
		*dst = inject_text(dst, &temp, NULL, NULL);
	}
	*start = *start + *f_qt;
}
