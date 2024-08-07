#include "../../includes/minishell.h"

char	*get_prev_dir(char *cwd)
{
	int	i;

	i = 0;
	while (cwd[i] != '\0')
		i++;
	while (cwd[i] != '/' && i != 0)
	{
		cwd[i] = '\0';
		i--;
	}
	return (cwd);
}

void	prev_path()
{
	char	*prev;
	char	cwd[4097];

	getcwd(cwd, sizeof(cwd));
	prev = get_prev_dir(cwd);
	chdir(prev);
}

void	cd_path(char *path)
{
	if (chdir(path) == -1)
		printf("ERROR\n");
	else
		return ;
}

void	cd_manager(char *argument)
{
	if (ft_strncmp(argument, "", 1) == 0)
		chdir(getenv("HOME"));//cd_home();
	else if (ft_strncmp(argument, "..", 2) == 0)
		prev_path();
	else
		cd_path(argument);
}
