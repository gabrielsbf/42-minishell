/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:40:56 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/09 01:42:27 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
A ideia é fazer a expansão dentro do function listener
Que deve tratar os argumentos antes de passar para as funções
*/
int	expand_variable(char **text, int i_cipher, t_env **envs)
{
	char	*env_name;
	char	*env_value;
	int		memory;

	memory = i_cipher + 1;
	while ((*text)[memory] != '\0' && is_env_available((*text)[memory]))
		memory++;
	env_name = ft_substr(*text, i_cipher + 1, memory - i_cipher - 1);
	env_value = check_name_in_env(envs, env_name);
	if (env_value == NULL)
		return (0);
	replace_text(text, env_name, env_value);
	free(env_name);
	return (1);
}

int	heredoc_before(char *text, int memory)
{
	while (memory > 0)
	{
		if (text[memory] == '<' && memory >= 1 && text[memory - 1] == '<')
			return (0);
		memory--;
	}
	return (1);
}

int	expansion_valid(char *text, int memory)
{
	printf("text is: %s - memory: %d", text, memory);
	if (heredoc_before(text, memory) == 0)
		return (0);
	if (is_between_quotes(text, memory) == 39
		|| is_between_quotes(text, memory) == 78)
		return (0);
	else if (is_between_quotes(text, memory))
		return (1);
	else
		return (1);
}

void	env_and_quotes(t_parse **parser, char *text, t_env **envs)
{
	int		i;
	int		expand_bool;
	char	*quotes_hand;

	i = 0;
	while (text[i] != '\0')
	{
		expand_bool = 0;
		if (text[i] == '$')
			expand_bool = expansion_valid(text, i);
		if (expand_bool == 1)
		{
			if (expand_variable(&text, i, envs))
				env_and_quotes(parser, text, envs);
		}
		i++;
	}
	quotes_hand = join_quotes(text);
	if ((*parser)->command_text)
		free((*parser)->command_text);
	(*parser)->command_text = ft_strdup(quotes_hand);
	free(quotes_hand);
}

// char	*env_and_quotes(t_parse **parser, t_env **envs)
// {
// 	int		i;
// 	char	*text;
// 	t_parse **head;

// 	head = parser;
// 	i = 0;
// 	while ((*parser) != NULL)
// 	{
// 		while ((*parser)->arguments[i] != NULL)
// 		{
// 			text = (*parser)->arguments[i];
// 			hand_cipher(parser, text, i, envs);
// 			i++;
// 		}
// 		(parser) = &(*parser)->next;
// 	}
// 	(parser) = head;
// }
