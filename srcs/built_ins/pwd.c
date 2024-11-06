#include "../../includes/minishell.h"

int	pwd(t_parse **parser)
{
	char	cwd[4097];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putendl_fd("PWD ERROR", 2);
		return (1);
	}
	else
		ft_putendl_fd(cwd, (*parser)->fd_out);
	return (0);
}
