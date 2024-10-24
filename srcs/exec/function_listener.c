#include "../../includes/minishell.h"

void	closing_fd(t_parse **parser)
{
	if ((*parser)->fd_in != 0)
		close((*parser)->fd_in);
	if ((*parser)->fd_out != 1)
		close((*parser)->fd_out);
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
		get_env(env, parser);
	else if (ft_strncmp((*parser)->main_command, "export", 7) == 0)
		export_to_env(env, (*parser)->arguments);
	else if (ft_strncmp((*parser)->main_command, "unset", 6) == 0)
		unset_from_env(env, (*parser)->arguments);
	else
		return (1);
	return (0);
}
/*
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
		return (1);
	return (0);
} */

void	dup_fds(t_parse **parser)
{
	if ((*parser)->fd_in != 0)
		dup2((*parser)->fd_in, STDIN_FILENO);
	if ((*parser)->fd_out != 1)
		dup2((*parser)->fd_out, STDOUT_FILENO);
	if ((*parser)->fd_out != 1 && (*parser)->fd_in != 0)
	{
		dup2((*parser)->fd_in, STDIN_FILENO);
		dup2((*parser)->fd_out, STDOUT_FILENO);
	}
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	int x = 0;
	if (built_ins_manager(parser, env) == 0 && !(*parser)->special_char)
			return ;
	while ((*parser))
	{
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
		{
			//dup_fds(parser);
			dup_fds(parser);
			if (built_ins_manager(parser, env) == 1)
				x = 1;
			if (x == 1)
			{
				x = 0;
				execution(parser, env, envp);
			}
			else
				ft_exit(parser, env);
		}
		waitpid((*parser)->pid, NULL, 0);
		closing_fd(parser);
		(*parser) = (*parser)->next;
	}
}
