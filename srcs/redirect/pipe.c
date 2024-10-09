#include "../../includes/minishell.h"

int	pipe_handler(t_parse **parser)
{
	t_parse *temp;
	int		fd;
	int		pip[2];
	int		pip_i;

	pip_i = pipe(pip);
	printf("%d\n", pip_i);
	fd = 2;
	temp = (*parser);
	while (temp != NULL)
	{
		temp->fd_in = ++fd;
		temp->fd_out = ++fd;
		//ft_putstr_fd("fd_int\n",temp->fd_in);
		//ft_putstr_fd("fd_out\n",temp->fd_out);
		temp = temp->next;
	}
	return 0;
}
