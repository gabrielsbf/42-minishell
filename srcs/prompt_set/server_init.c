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

void	server_loop(t_prompt **prompt_st, t_env **env, char **envp)
{
	(void)prompt_st;
	char	*line_read;
	char	*prefix_element;
	t_parse	*parser;
	while
	(1)
	{
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		add_history(line_read);
		parser = main_line_process(line_read, env);
		sp_char_validation(&parser, env);
		function_listener(&parser, env, envp);
		free(parser);
		free(prefix_element);
	}
}
