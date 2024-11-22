/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:31:19 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static void	validate_exit(t_parse **parser, t_env **env)
{
	if (!parser)
		sigquit_exit(env, parser);
	if (get_arg_len((*parser)) > 1)
		many_args_exit(env, parser);
}

void	ft_exit(t_parse **parser, t_env **env)
{
	int	temp;
	int	i;

	clear_history();
	temp = 0;
	validate_exit(parser, env);
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
