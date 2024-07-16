#include "../../includes/minishell.h"

int	ft_chdir(char *path)
{
	int	fd;

	fd = chdir(path);
	if(chdir != 0)
	{
		perror("Couldn't find the specified path\n");
	}
	return (0);
}
