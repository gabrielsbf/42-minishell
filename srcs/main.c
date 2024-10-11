#include "../includes/minishell.h"

void	sig_handler()
{
	if (RL_ISSTATE(RL_STATE_READCMD))
	{
		rl_replace_line("", 1);
		ioctl(1, TIOCSTI, "\n");
	}
	else
		ft_putendl_fd("", 1);
	rl_on_new_line();
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
	signal(SIGQUIT, SIG_IGN);
	server_loop(&prompt_in, &env, envp);
	return (0);
}
