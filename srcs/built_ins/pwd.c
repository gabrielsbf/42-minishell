#include "../../includes/minishell.h"

void	pwd(t_parse **parser)
{
	char	cwd[4097];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_putendl_fd("PWD ERROR", 2);
	else
		ft_putendl_fd(cwd, (*parser)->fd_out);
}
