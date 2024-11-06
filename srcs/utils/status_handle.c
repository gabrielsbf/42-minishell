#include "../../includes/minishell.h"

void	status_handle(int	status, t_env **env)
{
	if (status == 32512)
		update_env_status(env, 127);
	if (last_signal == 130)
		update_env_status(env, 130);
}
