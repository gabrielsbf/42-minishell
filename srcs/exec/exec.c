#include "../../includes/minishell.h"

int execution(t_parse **parser, char **envp)
{
	int	pid;
	int	i;
	char	*path;
	char	*s;

	i = 0;
	s = ft_strjoin("/", (*parser)->main_command);
	while ((*parser)->env_path[i] != NULL)
	{
		path = ft_strjoin((*parser)->env_path[i], s);
		if(access(path, F_OK & X_OK) != 0)
		{
			free(path);
			path = NULL;
		}
		else
			break;
		i++;
	}
	if (access((*parser)->main_command, R_OK & X_OK) != 0 && !path)
		return (2);
	pid = fork();
	if (pid == 0)
	{
		if (!path)
			execve((*parser)->main_command, (*parser)->arguments, envp);//must include exec_arguments in parser
		else
			execve(path, (*parser)->arguments, envp);
	}

	waitpid(pid, NULL, 0);
	return (0);
}
