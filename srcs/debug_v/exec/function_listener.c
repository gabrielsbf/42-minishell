/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_listener.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:02:17 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/19 19:05:33 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	closing_fd(t_parse *parser)
{
	t_parse	*temp;

	temp = parser;
	while (temp)
	{
		if (temp->fd_hdoc != 0)
			close(temp->fd_hdoc);
		if (temp->fd_in != STDIN_FILENO)
			close(temp->fd_in);
		if (temp->fd_out != STDOUT_FILENO)
			close(temp->fd_out);
		temp = temp->next;
	}
}

void	dup_fds(t_parse *parser)
{
	if (parser->fd_hdoc != 0)
	{
		close(parser->fd_in);
		parser->fd_in = parser->fd_hdoc;
		parser->fd_hdoc = 0;
	}
	if (parser->fd_in != STDIN_FILENO)
		dup2(parser->fd_in, STDIN_FILENO);
	if (parser->fd_out != STDOUT_FILENO)
		dup2(parser->fd_out, STDOUT_FILENO);
}

void	is_forking(t_parse **parser, t_parse *head, t_env **env, char **envp)
{
	while ((*parser))
	{
		if ((*parser)->main_command == NULL)
		{
			(*parser) = (*parser)->next;
			continue ;
		}
		(*parser)->pid = fork();
		if ((*parser)->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			pipe_built_ins(parser, env, head);
			dup_fds((*parser));
			closing_fd(head);
			execution(parser, env, envp);
		}
		(*parser) = (*parser)->next;
	}
}

void	function_listener(t_parse **parser, t_env **env, char **envp)
{
	t_parse	*head;

	head = (*parser);
	if (!(*parser)->special_char && (built_ins_manager(parser, env) == 0
			|| (*parser)->status != 0))
	{
		printf("BUiLTINS SEM FORK\n");
		printf("status = %d\n", (*parser)->status);
		closing_fd(head);
		return ;
	}
	printf("passed fork\n");
	is_forking(parser, head, env, envp);
	printf("in main process\n");
	(*parser) = head;
	closing_fd(head);
	while ((*parser))
	{
		waitpid((*parser)->pid, &(*parser)->status, 0);
		update_env_status(env, WEXITSTATUS((*parser)->status));
		throw_error(WEXITSTATUS((*parser)->status));
		(*parser) = (*parser)->next;
	}
	*parser = head;
}
