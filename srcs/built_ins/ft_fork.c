#include "../../includes/minishell.h"

void ft_fork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
		printf("pid ERROR");
	else if (pid == 0)
		printf("child process PID: %d\n", pid);
	else
		printf("parent process PID: %d\n", pid);
	/* kill(pid, SIGTERM);*/
}
