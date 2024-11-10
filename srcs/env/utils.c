/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:43:59 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/10 18:18:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*FUNCTION THAT MAYBE CAN GO TO LIBFT
BASIC FIND AND REPLACE*/
void	replace_text(char **text, char *find, char *replace)
{
	char	*dup_text;
	int		new_alloc;
	int		i_old;
	int		i_new;

	i_old = 0;
	i_new = 0;
	new_alloc = ft_strlen(*text) - ft_strlen(find) + ft_strlen(replace) + 2;
	dup_text = ft_strdup(*text);
	free_str(text);
	*text = (char *)malloc(new_alloc * sizeof(char));
	if (*text == NULL)
		return ;
	while (dup_text[i_old] != '\0')
	{
		if (dup_text[i_old] == '$')
		{
			if (expansion_valid(dup_text, i_old)
				&& ft_strncmp(&dup_text[i_old + 1], find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(&((*text)[i_new]), replace, ft_strlen(replace) + 1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
			}
		}
		if (dup_text[i_old] != '\0')
		{
			(*text)[i_new] = dup_text[i_old];
			i_old++;
			i_new++;
		}
	}
	free_str(&dup_text);
	(*text)[i_new] = '\0';
}

int	is_env_available(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}
