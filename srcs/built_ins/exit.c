/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:31:19 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/13 15:11:49 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_arg_len(t_parse *parser)
{
	t_parse	*temp;
	int	i;

	i = 0;
	temp = parser;
	if (!(parser)->arguments)
		return (0);
	while(temp->arguments[i] != NULL)
		i++;
	return (i);
}

void	sigquit_exit(t_env **env, t_parse **parser)
{
	free_env(env);
	free_parser(parser);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}

void	non_numeric_exit(t_env **env, t_parse **parser)
{
	free_env(env);
	free_parser(parser);
	ft_putstr_fd("exit\nnumeric argument required\n", STDOUT_FILENO);
	exit(2);
}

void	many_args_exit(t_env **env, t_parse **parser)
{
	free_env(env);
	free_parser(parser);
	ft_putstr_fd("exit\ntoo many arguments\n", STDOUT_FILENO);
	exit(1);
}

void	ft_exit(t_parse **parser, t_env **env)
{
	int	temp;
	int	i;

	clear_history();
	temp = 0;
	if (!parser)
		sigquit_exit(env, parser);
	if (get_arg_len((*parser)) > 1)
		many_args_exit(env, parser);
	if (get_arg_len((*parser)) == 1)
	{
		i = 0;
		while ((*parser)->arguments[0][i])
		{
			if (ft_isdigit((*parser)->arguments[0][i]) == 0)
				non_numeric_exit(env, parser);
			i++;
		}
		temp = ft_atoi((*parser)->arguments[0]);
	}
	free_env(env);
	free_parser(parser);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (temp)
		exit(temp);
	exit(EXIT_SUCCESS);
}
