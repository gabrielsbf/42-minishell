#include "../../includes/minishell.h"
/*redirect incomplete*/
void	redirect(t_parse **parser)
{
	t_parse *temp;

	temp = (*parser)->next;
	if (temp->main_command == NULL)
		return ;
	temp->fd_out = open(temp->main_command, O_WRONLY | O_CREAT, 0777);
	/* dup2 (temp->fd_out, STDOUT_FILENO); */
	close(temp->fd_out);
}
