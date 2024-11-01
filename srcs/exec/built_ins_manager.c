#include "../../includes/minishell.h"

int	built_ins_manager(t_parse **parser, t_env **env)
{
	if ((*parser)->main_command == NULL)
		return (0);
	if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
		ft_echo(parser);
	else if(ft_strncmp((*parser)->main_command, "exit", 5) == 0)
		ft_exit(parser, env);
	else if(ft_strncmp((*parser)->main_command, "pwd", 4) == 0)
		pwd(parser);
	else if (ft_strncmp((*parser)->main_command, "cd", 3) == 0)
		cd_manager((*parser)->arguments[0], env);
	else if (ft_strncmp((*parser)->main_command, "env", 4) == 0)
		get_env(env, parser);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
	else
		return (1);
	return (0);
}

void	pipe_built_ins(t_parse **parser, t_env **env)
{
	if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
		ft_echo(parser);
	else if(ft_strncmp((*parser)->main_command, "exit", 5) == 0)
		ft_exit(parser, env);
	else if(ft_strncmp((*parser)->main_command, "pwd", 4) == 0)
		pwd(parser);
	else if (ft_strncmp((*parser)->main_command, "cd", 3) == 0)
		cd_manager((*parser)->arguments[0], env);
	else if (ft_strncmp((*parser)->main_command, "env", 4) == 0)
		get_env(env, parser);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
	else
		return ;
	free_parser(parser);
	free_env(env);
	exit (1);
}
