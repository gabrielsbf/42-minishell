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

int	necessary_change(char *line_sub)
{
	int	i;

	i = 0;
	while (line_sub[i] != '\0')
	{
		if (line_sub[i] == 34 || line_sub[i] == 39)
		{
			i = get_next_match(line_sub, i, line_sub[i]);
			if (line_sub[i + 1] == 34 || line_sub[i] == 39)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*inject_text(char **line_start, char **line_end)
{
	char	*result;

	if (*line_start == NULL)
		 result = ft_strjoin("", (*line_end));
	else
	{
		result = ft_strjoin(*line_start, *line_end);
		free(*line_start);
	}
	free(*line_end);
	*line_start = NULL;
	*line_end = NULL;
	return (result);

}

char	*join_quotes(char *line_sub)
{
	char	*line_return;
	char	*temp_line;
	int		i;
	int		start;

	line_return = NULL;
	i = 0;
	start = 0;
	if (necessary_change(line_sub) == 0)
		return ft_strdup(line_sub);
	while (line_sub[i] != '\0')
	{
		while (line_sub[i] == 34 || line_sub[i] == 39)
		{
			printf("passing while line sub\n");
			i = get_next_match(line_sub, i, line_sub[i]);
			if (line_sub[i + 1] == 34 || line_sub[i + 1] == 39)
			{
				temp_line = ft_substr(line_sub, start, i - start);
				i++;
				start = i;
			}
			line_return = inject_text(&line_return, &temp_line);
			printf("works! line return is: %s\n", line_return);
		}
		i++;
	}
	temp_line = ft_substr(line_sub, start, i - start);
	line_return = inject_text(&line_return, &temp_line);
	return (line_return);
}

int	data_validation(char *line_read, char *prefix_element, t_parse **parser, t_env **env)
{
	char	*line_res;

	line_res = NULL;
	if (!line_read)
	{
		free(prefix_element);
		free(line_read);
		sigquit_exit(env, parser);
	}
	if (ft_strcmp(line_read, "") != 0)
		add_history(line_read);
	line_res =  join_quotes(line_read);
	*parser = main_line_process(line_res, env);
	if ((*parser) == NULL)
	{
		free(line_res);
		free(line_read);
		free(prefix_element);
		free_parser(parser);
		return (1);
	}
	free(prefix_element);
	free(line_read);
	free(line_res);
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
