#include "../../includes/minishell.h"

void	ft_echo(t_parse **parser)
{
	int i;
	int trailing;


	trailing = 0;
	i = 0;
	if (!*(*parser)->arguments)
	{
		ft_putstr_fd("\n", (*parser)->fd_out);
		return ;
	}
	if (ft_strncmp((*parser)->arguments[0], "-n", 3) == 0)
		i++;
	else
		trailing = 1;
	while ((*parser)->arguments[i] != NULL)
	{
		ft_putstr_fd((*parser)->arguments[i], (*parser)->fd_out);
		if ((*parser)->arguments[i + 1] != NULL)
			ft_putstr_fd(" ", (*parser)->fd_out);
		i++;
	}
	if (trailing == 1)
		ft_putstr_fd("\n", (*parser)->fd_out);
}
