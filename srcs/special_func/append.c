#include "../../includes/minishell.h"

int	append(t_parse **parser)
{
	t_parse	*temp;
	int		fd;
	int		std_o;

	std_o = dup(STDOUT_FILENO);
	fd = 0;
	temp = (*parser)->next;
	if (!temp->main_command)
		return 0;
	fd = open(temp->main_command, O_WRONLY | O_APPEND | O_CREAT);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (std_o);
}
