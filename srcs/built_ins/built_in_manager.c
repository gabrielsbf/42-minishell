#include "../../includes/minishell.h"

void	function_listener(t_parse **parser, t_env **env)
{

	env_expansion(parser, env);
	if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
	{
		ft_echo((*parser)->arguments);
		//o parse->flag está incompleto. mas o builtin e o parser já estão conectados
	}
	else if(ft_strncmp((*parser)->main_command, "exit", 5) == 0)
		exit(0);
	else if(ft_strncmp((*parser)->main_command, "pwd", 4) == 0)
		pwd();
	else if(ft_strncmp((*parser)->main_command, "ls", 3) == 0)
		list_directory(".");
	else if (ft_strncmp((*parser)->main_command, "cd", 3) == 0)
		cd_manager((*parser)->arguments[0], env);
	else if (ft_strncmp((*parser)->main_command, "env", 4) == 0)
		get_env(env);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
}
