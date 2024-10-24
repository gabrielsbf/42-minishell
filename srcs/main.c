#include "../includes/minishell.h"

int	g_status;

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
		g_status = 130;
	}
	return ;
}


int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	(void)argc;
	env = create_env_list(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	server_loop(&env, envp);
	return (0);
}
