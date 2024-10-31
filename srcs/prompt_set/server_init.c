#include "../../includes/minishell.h"

char	*prompt_prefix(void)
{
	char	*prompt_prefix;
	char	*temp;
	char	cwd[4097];

	prompt_prefix = ft_strjoin(getenv("LOGNAME"), "@");
	temp = ft_strjoin(prompt_prefix, getenv("USER"));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, ":");
	free(temp);
	temp = ft_strjoin(prompt_prefix, getcwd(cwd, sizeof(cwd)));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, "$ ");
	return (prompt_prefix);
}

int	data_validation(char *line_read, char *prefix_element, t_parse **parser, t_env **env)
{
	if (!line_read)
	{
		free(prefix_element);
		free(line_read);
		sigquit_exit(env, parser);
	}
	if (ft_strcmp(line_read, "") != 0)
		add_history(line_read);
	*parser = main_line_process(line_read, env);
	if ((*parser) == NULL)
	{
		free(line_read);
		free(prefix_element);
		free_parser(parser);
		return (1);
	}
	free(prefix_element);
	free(line_read);
	return (0);
}

void	server_loop(t_env **env, char **envp)
{
	char	*line_read;
	char	*prefix_element;
	t_parse	*parser;

	while
	(1)
	{
		rl_replace_line("", 0);
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		if (data_validation(line_read, prefix_element, &parser, env) == 1)
			continue ;
		sp_char_exec(&parser, env);
		env_expansion(&parser, env);
		print_parser_struct(parser);
		function_listener(&parser, env, envp);
		free_parser(&parser);
	}
}
