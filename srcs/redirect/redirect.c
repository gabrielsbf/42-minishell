#include "../../includes/minishell.h"
/*redirect incomplete*/
int	redirect(t_parse **parser)
{
	t_parse *temp;
	int		fd;
	int		std_o;

	std_o = dup(STDOUT_FILENO);
	temp = (*parser)->next;
	fd = 0;
	if (temp->main_command == NULL)
		return 0;
	fd = open(temp->main_command, O_WRONLY | O_CREAT, 0777);
	dup2 (fd, STDOUT_FILENO);
	close(fd);
	return (std_o);
}
