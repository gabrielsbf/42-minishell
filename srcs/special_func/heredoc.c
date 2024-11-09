#include "../../includes/minishell.h"

void	heredoc_last_signal(char *limit, int fd)
{
	if (last_signal == 130)
	{
		free(limit);
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
		heredoc_last_signal(limit, fd);
		if (!buffer || !ft_strcmp(limit, buffer))
			break;
		else if (buffer)
		{
			here_expansion(&buffer, env);
			ft_putendl_fd(buffer, fd);
			free(buffer);
		}
	}
	if (buffer)
		free(buffer);
	free(limit);
}
void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		last_signal = 130;
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

void	heredoc_exec(t_parse **parser, int redir_i, t_env **env)
{
	int		fd_hdoc[2];

	if (pipe(fd_hdoc) == -1)
		return ;
	(*parser)->pid = fork();
	if ((*parser)->pid == 0)
	{
		close(fd_hdoc[0]);
		signal(SIGINT, sig_heredoc);
		read_heredoc(parser, redir_i, fd_hdoc[1], env);
		close(fd_hdoc[1]);
		exit(0);
	}
	close(fd_hdoc[1]);
	(*parser)->fd_in = fd_hdoc[0];
	waitpid((*parser)->pid, NULL, 0);
}
