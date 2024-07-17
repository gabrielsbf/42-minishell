#include "../../includes/minishell.h"

void	function_listener(t_parse **parser)
{
	if (ft_strncmp((*parser)->main_command, "echo", 4) == 0)
	{
		ft_echo((*parser)->arguments);
		//o parse->flag está incompleto. mas o builtin e o parser já estão conectados
	}
	else if(ft_strncmp((*parser)->main_command, "exit", 4) == 0)
		exit(0);
}

