/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:42:45 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/17 00:03:11 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_here(char **text_in, char *find, char *replace)
{
	char	*line_here;
	int		new_alloc;
	int		i_old;
	int		i_new;

	i_old = 0;
	i_new = 0;
	new_alloc = ft_strlen((*text_in))
		- ft_strlen(find) + ft_strlen(replace) + 2;
	line_here = ft_strdup((*text_in));
	free_str(text_in);
	(*text_in) = ft_calloc(new_alloc, sizeof(char));
	while (line_here[i_old] != '\0')
	{
		if (line_here[i_old] == '$')
		{
			if (ft_strncmp(&line_here[i_old + 1], find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(&(*text_in)[i_new], replace, ft_strlen(replace) + 1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
			}
		}
		if (line_here[i_old] == '\0')
			break ;
		(*text_in)[i_new] = line_here[i_old];
		i_old++;
		i_new++;
	}
	free_str(&line_here);
	if ((*text_in)[i_new] != '\0')
		(*text_in)[i_new] = '\0';
}

int	expand_heredoc(char **text_in, int i_cipher, t_env **envs)
{
	char	*env_name;
	char	*env_value;
	int		memory;

	memory = i_cipher + 1;
	while ((*text_in)[memory] != '\0' && is_env_available((*text_in)[memory]))
		memory++;
	env_name = substr_val((*text_in), i_cipher + 1, memory);
	env_value = check_name_in_env(envs, env_name);
	if (env_value == NULL)
		replace_here(text_in, env_name, "");
	else
		replace_here(text_in, env_name, env_value);
	free_str(&env_name);
	return (1);
}

int	here_valid_qt(char *text, int memory)
{
	if (is_btw_qts(text, memory))
		return (1);
	else
		return (1);
}

void	here_expansion(char **text, t_env **envs)
{
	int	i;
	int	expand_bool;

	i = 0;
	while ((*text)[i] != '\0')
	{
		expand_bool = 0;
		if ((*text)[i] == '$')
			expand_bool = here_valid_qt(*text, i);
		if (expand_bool == 1)
		{
			if (expand_heredoc(text, i, envs))
				i = 0;
		}
		i++;
	}
}
