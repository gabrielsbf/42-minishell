#include "../../includes/minishell.h"

void	pwd()
{
	char	cwd[4097];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("ERROR");
	else
		printf("%s\n", cwd);
}
