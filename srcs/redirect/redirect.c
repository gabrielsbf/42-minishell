#include "../../includes/minishell.h"
/*redirect incomplete*/
void	check_redirect(t_parse *temp, int argument)
{
	int		fd;

	fd = 0;
	if (temp->arguments[argument] == NULL)
		return ;
	fd = open(temp->arguments[argument], O_WRONLY | O_CREAT, 0777);
	dup2 (fd, STDOUT_FILENO);
	close(fd);
}

void	redirect(t_parse **parser)
{
	t_parse	*temp = (*parser);
	int		i;

	i = 0;
	while (temp->arguments[i] != NULL)
	{
		if (temp->arguments[i][0] == '>')
			check_redirect(temp, ++i);
		i++;
	}

}
