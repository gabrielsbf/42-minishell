#include "../../includes/minishell.h"

void	function_listener(t_parse **parser, t_env **env)
{/*
	int	std_o;

	std_o = 1;
	env_expansion(parser, env);
	if ((*parser)->special_char != NULL
		&& ft_strcmp((*parser)->special_char, ">") == 0)
		std_o = redirect(parser); */
	while ((*parser) != NULL)
	{
		if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
			ft_echo(parser);
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
		/* dup2(std_o, STDOUT_FILENO); */
		(*parser) = (*parser)->next;
	}
}
