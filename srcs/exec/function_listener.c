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
		ft_exit(parser, env);
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
	else
		return (1);
	return (0);
}/*

void	built_ins_manager_exit(t_parse **parser, t_env **env)
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
		get_env(env);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
}*/

void	dup_fds(t_parse **parser)
{
	t_parse *temp;
	int x;

	x = 0;
	temp = (*parser);
	while (temp)
	{
		printf("\nfd in -> %d\nfd out -> %d\n", temp->fd_in, temp->fd_out);
		if (temp->head != NULL)
			x = dup2(temp->fd_in, STDIN_FILENO);
		if (temp->next != NULL)
			dup2(temp->fd_out, STDOUT_FILENO);
		temp = temp->next;
	}
	printf("%d\n", x);
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	while ((*parser))
	{
		if (built_ins_manager(parser, env) == 0)
			return ;
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
		{
			//dup_fds(parser);
			if ((*parser)->head != NULL)
				dup2((*parser)->fd_in, STDIN_FILENO);
			if ((*parser)->next != NULL)
				dup2((*parser)->fd_out, STDOUT_FILENO);
			execution(parser, envp);
		}
		waitpid((*parser)->pid, NULL, 0);
		if ((*parser)->head != NULL)
			close((*parser)->fd_in);
		if ((*parser)->next != NULL)
			close((*parser)->fd_out);
		(*parser) = (*parser)->next;
	}
}
