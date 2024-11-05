#include "../includes/minishell.h"

int	last_signal;

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (RL_ISSTATE(RL_STATE_READCMD))
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		last_signal = 130;
	}
	printf("%d\n", last_signal);
	return ;
}


int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	(void)argc;
	env = create_env_list(envp);
	add_env_status(&env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	server_loop(&env, envp);
	return (0);
}
