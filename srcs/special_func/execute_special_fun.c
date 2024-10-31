#include "../../includes/minishell.h"

char	*get_end_line(char *eof)
{
	int	i;
	int	len;

	i = 2;
	while (ft_isspace(eof[i]))
		i++;
	len = i;
	while (eof[len] != '\0' &&
		!ft_isspace(eof[len]))
		len++;
	return (ft_substr(eof, i, len - i));
}

void	read_heredoc(t_parse *parser, int redir_i, int fd)
{
	char	*limit;
	char	*buffer;

	limit = get_redir_name((parser)->redir[redir_i]);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || !ft_strcmp(limit, buffer))
			break;
		else if (buffer)
		{
			ft_putendl_fd(buffer, fd);
			free(buffer);
		}
	}
	free(limit);
	if (buffer)
		free(buffer);
}

void	heredoc_exec(t_parse *parser, int redir_i)
{
	int		fd_hdoc[2];

	if (pipe(fd_hdoc) == -1)
		return ;
	parser->pid = fork();
	if (parser->pid == 0)
	{
		read_heredoc(parser, redir_i, fd_hdoc[1]);
		exit(1);
	}
	close(fd_hdoc[1]);
	parser->fd_in = fd_hdoc[0];
	waitpid(parser->pid, NULL, 0);
}

/*função usada para identificar que tipo de redirect foi encontrado usando inteiros como identificadores*/
void	run_redir(t_parse *temp, int redir_i)
{
	if (temp->redir[redir_i][0] == '>' && (temp->redir[redir_i][1] != '>'
		&& temp->redir[redir_i][1] != '<'))
		redirect(temp, redir_i);
	if (temp->redir[redir_i][0] == '<' && (temp->redir[redir_i][1] != '>'
		&& temp->redir[redir_i][1] != '<'))
		redirect_in(temp, redir_i);
	if (temp->redir[redir_i][0] == '>' && temp->redir[redir_i][1] == '>')
		append(temp, redir_i);
	if (temp->redir[redir_i][0] == '<' && temp->redir[redir_i][1] == '<')
		heredoc_exec(temp, redir_i);
}

void	sp_char_exec(t_parse **parser)
{
	int		redir_i;
	t_parse	*temp;

	temp = (*parser);
	if (temp->special_char != NULL)
			pipe_handler(parser);
	while (temp)
	{
		redir_i = 0;
		if (!temp->redir && temp->next != NULL)
		{
			temp = temp->next;
			continue ;
		}
		if (!temp->redir && !temp->next)
			return ;
		while (temp->redir[redir_i])
		{
			run_redir(temp, redir_i);
			redir_i++;
		}
		temp = temp->next;
	}
}
