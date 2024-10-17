#include "../../includes/minishell.h"

int	pipe_handler(t_parse **parser)
{
	t_parse	**head = parser;
	int		fd[2];

	while ((*head)->next != NULL)
	{
		if(pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		else
		{
			(*head)->fd_in = fd[0];
			(*head)->fd_out = fd[1];
			dup2((*head)->fd_out, STDOUT_FILENO);
		}
		(*head) = (*head)->next;
	}
	return 0;
}
