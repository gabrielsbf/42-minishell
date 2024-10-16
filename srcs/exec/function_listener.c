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

int	built_ins_manager(t_parse **parser, t_env **env)
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
		return (1);
	return (0);
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	printf("---------------- FUNCTION LISTENER ----------------");
	while ((*parser) != NULL)
	{
		if (built_ins_manager(parser, env) == 0 && !(*parser)->special_char)
			return ;
		else
		{
			if ((*parser)->pid != 0)
				(*parser)->pid = fork();
			execution(parser, envp);
		}
		if ((*parser)->fd_out != 1)
		{
			close((*parser)->fd_out);
		}
		if ((*parser)->fd_in != 0)
		{
			dup2(STDIN_FILENO, (*parser)->fd_in);
			close((*parser)->fd_in);
		}
		if ((*parser)->pid == 0)
			exit(0);
		(*parser) = (*parser)->next;
	}
	printf("---------------- FUNCTION LISTENER ----------------");
}
