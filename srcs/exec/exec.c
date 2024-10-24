#include "../../includes/minishell.h"

int	get_arg_len(t_parse *parser)
{
	t_parse	*temp;
	int	i;

	i = 0;
	temp = parser;
	while(temp->arguments[i] != NULL)
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

void	create_execargs(t_parse **parser)
{
	int		arg_len;
	int		i;

	i = 0;
	arg_len = get_arg_len((*parser)) + 1;
	(*parser)->exec_txt = ft_calloc(sizeof(char *), arg_len + 1);
	while (arg_len > i)
	{
		if (i == 0)
			(*parser)->exec_txt[i] = ft_strdup((*parser)->main_command);
		else
			(*parser)->exec_txt[i] = ft_strdup((*parser)->arguments[i - 1]);
		i++;
	}
	(*parser)->exec_txt[i] = NULL;
}

int execution(t_parse **parser, t_env **env, char **envp)
{
	int		i;
	char	*path;
	char	*s;

	(void)env;
	create_execargs(parser);
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
			break ;
		i++;
	}
	free(s);
	if (access((*parser)->main_command, R_OK & X_OK) != 0 && !path)
		ft_exit(parser, env);
	if (!path)
		execve((*parser)->main_command, (*parser)->exec_txt, envp);//must include exec_arguments in parser
	else
		execve(path, (*parser)->exec_txt, envp);
	return (0);
}
