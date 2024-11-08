#include "../../includes/minishell.h"

void	read_heredoc(t_parse **parser, int redir_i, int fd, t_env **env)
{
	char	*limit;
	char	*buffer;

	limit = get_redir_name((*parser)->redir[redir_i]);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strcmp(limit, buffer))
			break;
		else if (buffer)
		{
			here_expansion(&buffer, env);
			ft_putendl_fd(buffer, fd);
			free(buffer);
		}
	}
	free(limit);
	if (buffer)
		free(buffer);
}

void	heredoc_exec(t_parse **parser, int redir_i, t_env **env)
{
	int		fd_hdoc[2];

	if (pipe(fd_hdoc) == -1)
		return ;
	(*parser)->pid = fork();
	if ((*parser)->pid == 0)
	{
		read_heredoc(parser, redir_i, fd_hdoc[1], env);
		close(fd_hdoc[0]);
		close(fd_hdoc[1]);
		exit(1);
	}
	close(fd_hdoc[1]);
	(*parser)->fd_in = fd_hdoc[0];
	waitpid((*parser)->pid, NULL, 0);
}
