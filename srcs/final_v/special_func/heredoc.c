/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:16:42 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/21 19:56:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	heredoc_g_last_signal(char *limit, int fd)
{
	if (g_last_signal == 130)
	{
		free_str(&limit);
		close (fd);
		exit(130);
	}
}

void	read_heredoc(t_parse **parser, int redir_i, int fd, t_env **env)
{
	char	*limit;
	char	*buffer;

	limit = get_redir_name((*parser)->redir[redir_i]);
	while (1)
	{
		buffer = readline("> ");
		heredoc_g_last_signal(limit, fd);
		if (!buffer || !ft_strcmp(limit, buffer))
			break ;
		else if (buffer)
		{
			here_expansion(&buffer, env);
			ft_putendl_fd(buffer, fd);
			free_str(&buffer);
		}
	}
	if (buffer)
		free_str(&buffer);
	free_str(&limit);
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_last_signal = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		signal(SIGINT, SIG_IGN);
	}
	else
	{
		ioctl(1, TIOCSTI, 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	heredoc_exec(t_parse **parser, int redir_i, t_env **env, t_parse *head)
{
	int		fd_hdoc[2];

	if (pipe(fd_hdoc) == -1)
		return ;
	(*parser)->pid = fork();
	if ((*parser)->pid == 0)
	{
		closing_fd(head);
		close(fd_hdoc[0]);
		signal(SIGINT, sig_heredoc);
		read_heredoc(parser, redir_i, fd_hdoc[1], env);
		close(fd_hdoc[1]);
		free_parser(parser);
		free_env(env);
		exit(0);
	}
	waitpid((*parser)->pid, NULL, 0);
	close(fd_hdoc[1]);
	if ((*parser)->fd_hdoc != 0)
		close((*parser)->fd_hdoc);
	(*parser)->fd_hdoc = fd_hdoc[0];
	waitpid((*parser)->pid, NULL, 0);
}
