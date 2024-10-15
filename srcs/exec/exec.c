#include "../../includes/minishell.h"

int	get_arg_len(t_parse **parser)
{
	t_parse	*temp;
	int	i;

	i = 0;
	temp = (*parser);
	while(temp->arguments[i])
		i++;
	return (i);
}

void	get_execargs(char	*args, char **exec_arg, int	arr_i)
{
	int		i;

	i = 0;
	while (args[i] != '\0')
	{
		exec_arg[arr_i][i] = args[i];
		i++;
	}
}

char	**create_execargs(t_parse **parser)
{
	char	**exec_args;
	int		arg_len;
	int		i;

	i = 0;
	arg_len = get_arg_len(parser) + 1;
	exec_args = ft_calloc(sizeof(char *), arg_len + 1);
	while (arg_len > i)
	{
		if (i == 0)
		{
			exec_args[i] = ft_calloc(sizeof(char), ft_strlen((*parser)->main_command) + 1);
			get_execargs((*parser)->main_command, exec_args, i);
		}
		else
		{
			exec_args[i] = ft_calloc(sizeof(char), ft_strlen((*parser)->arguments[i - 1]) + 1);
			get_execargs((*parser)->arguments[i - 1], exec_args, i);
		}
		i++;
	}
	return (exec_args);
}

int execution(t_parse **parser, char **envp)
{
	int		i;
	char	*path;
	char	**exec_args;
	char	*s;

	exec_args = create_execargs(parser);
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
	if ((*parser)->pid == 0)
	{
		if (!path)
			execve((*parser)->main_command, exec_args, envp);//must include exec_arguments in parser
		else
			execve(path, exec_args, envp);
	}
	return (0);
}
