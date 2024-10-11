#include "../../includes/minishell.h"
/*
char	*path_name(char **envp)
{
	char	*path_name;
	char ***temp;

	if(!envp)
		return (NULL);
	(*temp) = envp;
	while ((*temp))
	{
		if (ft_strcmp((*temp), "PATH") == 0)
			return (get_env_value(*temp));
		(*temp)++;
	}
	return (path_name);
}*/

int execution(t_parse **parser, char **envp)
{
	int	pid;
	int	i;
	char	*path;
	char	*s;

	i = 0;
	s = NULL;
	s = ft_strjoin("/", (*parser)->main_command);
	while ((*parser)->env_path[i] != NULL)
	{
		path = ft_strjoin((*parser)->env_path[i], s);
		if(access(path, F_OK & X_OK) != 0)
			free(path);
		else
			break;
		i++;
	}
	if (!path)
		return (2);
	pid = fork();
	if (pid == 0)
		execve(path, (*parser)->arguments, envp);
	waitpid(pid, NULL, 0);
	return (0);
}
