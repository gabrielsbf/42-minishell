#include "../../includes/minishell.h"
/*redirect incomplete*/
void	redirect(t_parse **parser)
{
	t_parse *temp;
	int		fd;

	temp = (*parser)->next;
	fd = 0;
	if (temp->main_command == NULL)
		return ;
	fd = open(temp->main_command, O_WRONLY | O_CREAT, 0777);
	dup2 (fd, STDOUT_FILENO);
	close(fd);
}
