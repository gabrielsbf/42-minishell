#include "../includes/minishell.h"

int main(void)
{
	t_prompt *prompt_in;
	t_env	*env;

	env = create_env_list();
	prompt_in = init_prompt_struct();
	server_loop(&prompt_in, &env);
	return (0);
}
