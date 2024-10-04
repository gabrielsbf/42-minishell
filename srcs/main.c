#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	char *prefix = prompt_prefix();
	if (sig == SIGINT)
		printf("\n%s", prefix);
	else if (sig == SIGQUIT)
		printf("%s", prefix);
	free(prefix);
}

int main(int argc, char **argv, char **envp)
{
	t_prompt *prompt_in;
	t_env	*env;

	(void)argv;
	(void)argc;
	env = create_env_list(envp);
	prompt_in = init_prompt_struct();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	server_loop(&prompt_in, &env);
	return (0);
}
