#include "../../includes/minishell.h"

int	pipe_handler(t_parse **parser)
{
	t_parse	**head;
	int		fd[2];

	head = parser;
	while ((*parser)->next != NULL)
	{
		if(pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		else
		{

			(*parser)->fd_in = fd[0];
			(*parser)->fd_out = fd[1];
			// dup2((*parser)->fd_out, STDOUT_FILENO);

		}
		parser = &(*parser)->next;
	}
	parser = head;
	return 0;
}
