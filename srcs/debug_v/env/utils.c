/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:43:59 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/18 00:50:27 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_nxt_step(char **text, char *dup_text, int *i_old, int *i_new)
{
	if (dup_text[*i_old] == '\0')
		return ;
	(*text)[*i_new] = dup_text[*i_old];
	(*i_old)++;
	(*i_new)++;
}

static char	*replace_allocation(char **t_in, char *find, char *rep, int *flip)
{
	int		new_alloc;
	char	*l_return;

	*flip = 0;
	new_alloc = ft_strlen((*t_in))
		- ft_strlen(find) + ft_strlen(rep) + 2;
	l_return = ft_strdup((*t_in));
	if (!l_return)
		return (NULL);
	free_str(t_in);
	(*t_in) = ft_calloc(new_alloc, sizeof(char));
	return (l_return);
}

/*FUNCTION THAT MAYBE CAN GO TO LIBFT
BASIC FIND AND REPLACE*/
void	replace_text(char **text, char *find, char *replace)
{
	char	*dup_text;
	int		i_old;
	int		i_new;
	int		flip;

	i_old = 0;
	i_new = 0;
	dup_text = replace_allocation(text, find, replace, &flip);
	while (dup_text[i_old] != '\0')
	{
		if (dup_text[i_old] == '$')
		{
			if (flip == 0 && expansion_valid(dup_text, i_old)
				&& ft_strncmp(&dup_text[i_old + 1], find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(&((*text)[i_new]), replace, ft_strlen(replace) + 1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
				flip = 1;
			}
		}
		check_nxt_step(text, dup_text, &i_old, &i_new);
	}
	free_str(&dup_text);
}

void	replace_here(char **text_in, char *find, char *replace)
{
	char	*line_here;
	int		i_old;
	int		i_new;
	int		flip;

	i_old = 0;
	i_new = 0;
	line_here = replace_allocation(text_in, find, replace, &flip);
	while (line_here[i_old] != '\0')
	{
		if (line_here[i_old] == '$')
		{
			if (flip == 0 && ft_strncmp(&line_here[i_old + 1],
					find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(&(*text_in)[i_new], replace, ft_strlen(replace) + 1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
				flip = 1;
			}
		}
		check_nxt_step(text_in, line_here, &i_old, &i_new);
	}
	free_str(&line_here);
}
