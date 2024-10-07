#include "../../includes/minishell.h"

void	pwd()
{
	char	cwd[4097];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_putendl_fd("PWD ERROR", 2);
	else
		printf("%s\n", cwd);
}
