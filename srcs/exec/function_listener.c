#include "../../includes/minishell.h"

void	closing_fd(t_parse **parser)
{
	if ((*parser)->fd_in != 0)
		close((*parser)->fd_in);
	if ((*parser)->fd_out != 1)
		close((*parser)->fd_out);
}

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
	if (!(*parser)->special_char && built_ins_manager(parser, env) == 0)
			return ;
	while ((*parser))
	{
		if ((*parser)->main_command == NULL)
		{
			(*parser) = (*parser)->next;
			continue;
		}
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			dup_fds(parser);
			pipe_built_ins(parser, env);
			execution(parser, env, envp);
		}
		waitpid((*parser)->pid, NULL, 0);
		closing_fd(parser);
		(*parser) = (*parser)->next;
	}
}
