/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:42:45 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/17 23:57:06 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
