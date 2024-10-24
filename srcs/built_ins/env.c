#include "../../includes/minishell.h"

void get_env(t_env **env, t_parse **parser)
{
	t_env *swap;

	swap = (*env);
	while (swap != NULL)
	{
		ft_putstr_fd(swap->name, (*parser)->fd_out);
		ft_putstr_fd("=", (*parser)->fd_out);
		ft_putendl_fd(swap->value, (*parser)->fd_out);
		swap = swap->next;
	}
}
