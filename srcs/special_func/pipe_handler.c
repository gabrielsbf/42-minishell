#include "../../includes/minishell.h"

int	pipe_handler(t_parse **parser)
{
	t_parse	*temp;
	int		fd[2];

	temp = (*parser);
	while (temp != NULL)
	{
		if(pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		else
		{
			temp->fd_in = fd[0];
			temp->fd_out = fd[1];
		}
		temp = temp->next;
	}
	return 0;
}
