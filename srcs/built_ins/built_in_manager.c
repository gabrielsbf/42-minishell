#include "../../includes/minishell.h"

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	printf("EXECUTION PRINT\n-------------------------------------------------\n");
	while ((*parser) != NULL)
	{
		if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
			ft_echo(parser);
		else if(ft_strncmp((*parser)->main_command, "exit", 5) == 0)
			exit(0);
		else if(ft_strncmp((*parser)->main_command, "pwd", 4) == 0)
			pwd();
		else if (ft_strncmp((*parser)->main_command, "cd", 3) == 0)
			cd_manager((*parser)->arguments[0], env);
		else if (ft_strncmp((*parser)->main_command, "env", 4) == 0)
			get_env(env);
		else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
			export_to_env(env, (*parser)->arguments);
		else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
			unset_from_env(env, (*parser)->arguments);
		else
		{
			if ((*parser)->pid != 0)
				(*parser)->pid = fork();
			execution(parser, envp);
			waitpid((*parser)->pid, NULL, 0);
		}
		if ((*parser)->next != NULL && (*parser)->fd_out != 1)
		{
			close((*parser)->fd_in);
			close((*parser)->fd_out);
		}
		if ((*parser)->pid == 0)
			exit(0);
		(*parser) = (*parser)->next;
		printf("-------------------------------------------------\n");
	}
}
