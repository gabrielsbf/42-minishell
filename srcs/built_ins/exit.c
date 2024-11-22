/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:31:19 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/20 01:20:08 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	verify_num_exit(t_parse **parser, t_env **env)
{
	int	i;

	i = 0;
	while ((*parser)->arguments[0][i])
	{
		if (ft_isdigit((*parser)->arguments[0][i]) == 0)
			non_numeric_exit(env, parser);
		i++;
	}
	return (ft_atoi((*parser)->arguments[0]));
}

void	ft_exit(t_parse **parser, t_env **env)
{
	int	temp;

	clear_history();
	temp = 0;
	if (!parser)
		sigquit_exit(env, parser);
	if (get_arg_len((*parser)) > 1)
		many_args_exit(env, parser);
	if (get_arg_len((*parser)) == 1)
		temp = verify_num_exit(parser, env);
	free_env(env);
	free_parser(parser);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (temp)
		exit(temp);
	exit(EXIT_SUCCESS);
}
