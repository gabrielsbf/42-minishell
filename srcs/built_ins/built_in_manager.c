#include "../../includes/minishell.h"

void	function_listener(t_parse **parser)
{
	env_expansion(parser);
	if (ft_strncmp((*parser)->main_command, "echo", 4) == 0)
	{
		ft_echo((*parser)->arguments);
		//o parse->flag está incompleto. mas o builtin e o parser já estão conectados
	}
	else if(ft_strncmp((*parser)->main_command, "exit", 4) == 0)
		exit(0);
	else if(ft_strncmp((*parser)->main_command, "pwd", 3) == 0)
		pwd();
	else if(ft_strncmp((*parser)->main_command, "ls", 2) == 0)
		list_directory(".");
	else if (ft_strncmp((*parser)->main_command, "cd", 2) == 0)
		cd_manager((*parser)->arguments[0]);
	else if (ft_strncmp((*parser)->main_command, "env", 3) == 0)
		printf("Doing env\n");//get_env();
}

