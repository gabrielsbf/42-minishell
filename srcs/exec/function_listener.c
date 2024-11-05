#include "../../includes/minishell.h"

void	printfds(t_parse *parser)
{
	printf("fd_in->%d\n", parser->fd_in);
	printf("fd_out->%d\n", parser->fd_out);
}

void	closing_fd(t_parse *parser)
{
	t_parse *temp;

	temp = parser;
	while (temp)
	{
		if (temp->fd_in != STDIN_FILENO)
			close(temp->fd_in);
		if (temp->fd_out != STDOUT_FILENO)
			close(temp->fd_out);
		temp = temp->next;
	}
}

void	dup_fds(t_parse *parser)
{
	if (parser->fd_in != STDIN_FILENO)
		dup2(parser->fd_in, STDIN_FILENO);
	if (parser->fd_out != STDOUT_FILENO)
		dup2(parser->fd_out, STDOUT_FILENO);
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	t_parse	*head = (*parser);

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
			pipe_built_ins(parser, env);
			dup_fds((*parser));
			closing_fd(head);
			execution(parser, env, envp);
		}
		(*parser) = (*parser)->next;
	}
	t_parse *temp = head;
	while (temp)
	{
		closing_fd(head);
		waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
}
