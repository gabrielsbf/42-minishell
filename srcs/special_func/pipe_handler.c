#include "../../includes/minishell.h"

int	pipe_num(t_parse **parser)
{
	t_parse *temp;
	int	pipe_num;

	pipe_num = 0;
	temp = (*parser);
	while(temp)
	{
		if (temp->special_char != NULL && ft_strcmp(temp->special_char, "|") == 0)
			pipe_num++;
		temp = temp->next;
	}
	return (pipe_num);
}

int	pipe_handler(t_parse **parser)
{
	t_parse	*temp;
	int		fd[2];
	int	last_pipe;

	/* last_pipe = pipe_num(parser); */
	last_pipe = 0;
	temp = (*parser);
	while (temp->next != NULL)
	{

		if (last_pipe != 0)
			temp->fd_in = last_pipe;
		if(pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		last_pipe = fd[0];
		temp->fd_out = fd[1];
		// dup2((*parser)->fd_out, STDOUT_FILENO);
		temp = temp->next;
	}
	temp->fd_in = last_pipe;
	return 0;
}
