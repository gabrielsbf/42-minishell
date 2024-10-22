 #include "../../includes/minishell.h"

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

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_parser(t_parse **parser)
{
	t_parse	*temp;

	if (!(*parser))
		return ;
	while ((*parser))
	{
		temp = (*parser);
		free_args((*parser)->arguments);
		free_args((*parser)->env_path);
		free_args((*parser)->exec_txt);
		free_args((*parser)->flags);
		free((*parser)->command_text);
		free((*parser)->entire_text);
		free((*parser)->main_command);
		free((*parser)->special_char);
		(*parser)->head = NULL;
		(*parser) = (*parser)->next;
		free(temp);
	}
}


void	free_all(t_env **env, t_parse **parser)
{
	free_env(env);
	free_parser(parser);
}

void	sigquit_exit(t_env **env, t_parse **parser)
{
	free_all(env, parser);
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}

void	non_numeric_exit(t_env **env, t_parse **parser)
{
	free_all(env, parser);
	ft_putstr_fd("exit\nnumeric argument required\n", STDOUT_FILENO);
	exit(2);
}

void	many_args_exit(t_env **env, t_parse **parser)
{
	free_all(env, parser);
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
	free_all(env, parser);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (temp)
		exit(temp);
	exit(EXIT_SUCCESS);
}
