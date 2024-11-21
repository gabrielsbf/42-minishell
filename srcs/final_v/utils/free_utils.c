/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:07:51 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while ((*env))
	{
		temp = (*env);
		free((*env)->value);
		free((*env)->name);
		(*env)->value = NULL;
		(*env)->name = NULL;
		(*env)->head = NULL;
		(*env) = (*env)->next;
		free(temp);
	}
}

void	free_str(char **str)
{
	if (!(str) || !(*str))
		return ;
	free((*str));
	(*str) = NULL;
}

void	free_str_arr(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args && args[i] != NULL)
	{
		free_str(&args[i]);
		i++;
	}
	if (args)
		free(args);
	args = NULL;
}

void	free_parser_str(t_parse **parser)
{
	if ((*parser)->command_text)
		free_str(&(*parser)->command_text);
	if ((*parser)->entire_text)
		free_str(&(*parser)->entire_text);
	if ((*parser)->main_command)
		free_str(&(*parser)->main_command);
	if ((*parser)->special_char)
		free_str(&(*parser)->special_char);
}

void	free_parser(t_parse **parser)
{
	t_parse	*temp;

	temp = NULL;
	if (!(*parser))
		return ;
	while ((*parser))
	{
		temp = *parser;
		free_str_arr((*parser)->arguments);
		free_str_arr((*parser)->env_path);
		free_str_arr((*parser)->exec_txt);
		free_str_arr((*parser)->redir);
		free_parser_str(parser);
		(*parser)->head = NULL;
		(*parser) = (*parser)->next;
		free(temp);
	}
}
