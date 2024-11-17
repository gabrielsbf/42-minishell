/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:28:44 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/16 23:51:35 by gabrfern         ###   ########.fr       */
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

char	*exclude_spaces(char *line_sub)
{
	char	*line_return;
	char	*temp_line;
	int		i;
	int		start;

	i = 0;
	start = 0;
	line_return = NULL;
	while (line_sub[i] != '\0')
	{
		while (line_sub[i] != '\0' && (!ft_isspace(line_sub[i])
				|| is_btw_qts(line_sub, i)))
			i++;
		if (i != start)
		{
			if (line_sub[i] == '\0')
				temp_line = substr_val(line_sub, start, i);
			else
				temp_line = substr_val(line_sub, start, i + 1);
			line_return = inject_text(&line_return, &temp_line, NULL, NULL);
			start = i;
		}
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

/*
(finished) This function do a realloc between two arrays of char pointers
It will be on the sequence -> the first char ** will be at the
start and the second will be at the end.
*/
char	**ft_realloc_two_lists(char **str, char **str_new)
{
	int		new_alloc;
	int		i;
	int		i_last;
	char	**new_arr;

	i = 0;
	i_last = 0;
	new_alloc = count_arr_nb(str) + count_arr_nb(str_new) + 1;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str && str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		i++;
	}
	while (str_new && str_new[i_last] != NULL)
		new_arr[i++] = ft_strdup(str_new[i_last++]);
	new_arr[i] = NULL;
	free_str_arr(str);
	free_str_arr(str_new);
	return (new_arr);
}

/*
(finished) This function do a realloc of an array of char pointers and puts a new
char pointer at the end of the array.
*/
char	**ft_realloc_list_and_str(char **str, char *str_new)
{
	int		new_alloc;
	int		i;
	char	**new_arr;
	int		is_null;

	i = 0;
	new_alloc = count_arr_nb(str) + 2;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	if (str != NULL)
		is_null = 0;
	else
		is_null = 1;
	while (is_null == 0 && str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str_new);
	new_arr[i + 1] = NULL;
	free_str(&str_new);
	free_str_arr(str);
	return (new_arr);
}
