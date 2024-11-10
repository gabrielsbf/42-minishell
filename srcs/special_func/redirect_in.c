#include "../../includes/minishell.h"

void	redirect_in(t_env **env, t_parse **parser, int redir_i)
{
	char	*file_name;

	file_name = get_redir_name((*parser)->redir[redir_i]);
	if ((*parser)->fd_in != 0)
		close((*parser)->fd_in);
	(*parser)->fd_in = open(file_name, O_RDONLY);
	if ((*parser)->fd_in == -1)
	{
		(*parser)->status = 1;
		update_env_status(env, 1);
		ft_putendl_fd("input redirect: ERROR", 2);
	}
	if ((*parser)->fd_in == -1)
		free_str(&file_name);
}
