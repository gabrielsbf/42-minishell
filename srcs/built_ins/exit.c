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

void	ft_exit(t_parse **parser, t_env **env)
{
	int	temp;
	int	i;

	if (!parser)
		sigquit_exit(env, parser);
	if (get_arg_len((*parser)) > 2)
		many_args_exit(env, parser);
	if (get_arg_len((*parser)) == 2)
	{
		i = 0;
		while ((*parser)->arguments[1][i])
		{
			if (ft_isdigit((*parser)->arguments[1][i]) == 0)
				non_numeric_exit(env, parser);
			i++;
		}
		temp = ft_atoi((*parser)->arguments[1]);
	}
	free_env(env);
	free_parser(parser);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (temp)
		exit(temp);
	exit(EXIT_SUCCESS);
}
