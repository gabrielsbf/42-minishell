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
	t_parse	**head;
	int		fd[2];
	int	pipe_count;

	/* pipe_count = pipe_num(parser); */
	pipe_count = 0;
	head = parser;
	while ((*parser)->next != NULL)
	{

		if (pipe_count != 0)
			(*parser)->fd_in = pipe_count;
		if(ft_strcmp((*parser)->special_char, "|") == 0 && pipe(fd) == -1)
			return (ft_putendl_fd("PIPE_ERROR", 2), 0);
		else
		{
			pipe_count = fd[0];
			(*parser)->fd_out = fd[1];
			// dup2((*parser)->fd_out, STDOUT_FILENO);
		}
		parser = &(*parser)->next;
	}
	parser = head;
	return 0;
}
