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
	free(temp);
	return (prompt_prefix);
}

int	data_validation(char **line_read, char **prefix_element, t_parse **parser, t_env **env)
{
	if (!(*line_read))
	{
		free_str(prefix_element);
		free_str(line_read);
		sigquit_exit(env, parser);
	}
	if (ft_strcmp(*line_read, "") != 0)
		add_history(*line_read);
	*parser = main_line_process(*line_read, env);
	if ((*parser) == NULL)
	{
		free_str(line_read);
		free_str(prefix_element);
		free_parser(parser);
		if (last_signal == 130)
			update_env_status(env, last_signal);
		else
			update_env_status(env, 2);
		return (1);
	}
	free_str(prefix_element);
	free_str(line_read);
	return (0);
}

void	server_loop(t_env **env, char **envp)
{
	char	*line_read;
	char	*prefix_element;
	t_parse	*parser;

	parser = NULL;
	while
	(1)
	{
		last_signal = 0;
		rl_replace_line("", 0);
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		if (data_validation(&line_read, &prefix_element, &parser, env) == 1)
			continue ;
		sp_char_exec(&parser, env);
		print_parser_struct(parser);
		function_listener(&parser, env, envp);
		if (last_signal != 0)
			update_env_status(env, last_signal);
		free_parser(&parser);
	}
}
