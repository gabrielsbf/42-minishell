#include "../../includes/minishell.h"

char	*prompt_prefix(void)
{
	char	*prompt_prefix;
	char	*temp;
	char	cwd[4097];

	prompt_prefix = ft_strjoin(getenv("LOGNAME"), "@");
	temp = ft_strjoin(prompt_prefix, getenv("NAME"));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, ":");
	free(temp);
	temp = ft_strjoin(prompt_prefix, getcwd(cwd, sizeof(cwd)));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, "$ ");
	return (prompt_prefix);
}

void	server_loop(t_prompt **prompt_st, t_env **env)
{
	(void)prompt_st;
	char	*line_read;
	char	*prefix_element;
	while
	(1)
	{
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		if (ft_strcmp(line_read, "") == 0)
		{
			free(prefix_element);
			free(line_read);
			continue;
		}
		add_history(line_read);
		main_line_process(line_read, env);
		free(prefix_element);
	}
}
