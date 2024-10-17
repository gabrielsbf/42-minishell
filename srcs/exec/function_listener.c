#include "../../includes/minishell.h"

void	closing_fd(t_parse **parser)
{
	t_parse	*temp;

	temp = (*parser)->head;
	while (temp->next)
	{
		close(temp->fd_in);
		close(temp->fd_out);
		temp = temp->next;
	}
}

void	built_ins_manager(t_parse **parser, t_env **env)
{
	if (ft_strncmp((*parser)->main_command, "echo", 5) == 0)
		ft_echo(parser);
	else if(ft_strncmp((*parser)->main_command, "exit", 5) == 0)
		exit(0);
	else if(ft_strncmp((*parser)->main_command, "pwd", 4) == 0)
		pwd(parser);
	else if (ft_strncmp((*parser)->main_command, "cd", 3) == 0)
		cd_manager((*parser)->arguments[0], env);
	else if (ft_strncmp((*parser)->main_command, "env", 4) == 0)
		get_env(env);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
	g_status = 1;
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	if (g_status == -1)
	{
		g_status = 0;
		return ;
	}
	while ((*parser) != NULL)
	{
		built_ins_manager(parser, env);
	  if ((*parser)->pid != 0)
		{
			printf("%d\n", (*parser)->pid);
			(*parser)->pid = fork();
			execution(parser, envp);
			waitpid((*parser)->pid, NULL, 0);
		}
		if ((*parser)->pid == 0)
			exit(0);
		(*parser) = (*parser)->next;
	}
}
