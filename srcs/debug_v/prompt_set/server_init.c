/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:55:53 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/16 23:57:29 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prompt_prefix(void)
{
	char	*prompt_prefix;
	char	*temp;
	char	cwd[4097];

	prompt_prefix = ft_strjoin(getenv("LOGNAME"), "@");
	temp = ft_strjoin(prompt_prefix, getenv("USER"));
	free_str(&prompt_prefix);
	prompt_prefix = ft_strjoin(temp, ":");
	free_str(&temp);
	temp = ft_strjoin(prompt_prefix, getcwd(cwd, sizeof(cwd)));
	free_str(&prompt_prefix);
	prompt_prefix = ft_strjoin(temp, "$ ");
	free_str(&temp);
	return (prompt_prefix);
}

int	data_validation(char **line, char **prefix, t_parse **parser, t_env **env)
{
	if (!(*line))
	{
		free_str(prefix);
		free_str(line);
		sigquit_exit(env, parser);
	}
	if (ft_strcmp(*line, "") != 0)
		add_history(*line);
	*parser = main_line_process(*line, env);
	if ((*parser) == NULL)
	{
		free_str(line);
		free_str(prefix);
		free_parser(parser);
		if (g_last_signal == 130)
			update_env_status(env, g_last_signal);
		else
			update_env_status(env, 2);
		return (1);
	}
	free_str(prefix);
	free_str(line);
	return (0);
}

void	server_loop(t_env **env, char **envp)
{
	char	*line_read;
	char	*prefix_element;
	t_parse	*parser;

	parser = NULL;
	while (1)
	{
		g_last_signal = 0;
		rl_replace_line("", 0);
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		if (data_validation(&line_read, &prefix_element, &parser, env) == 1)
			continue ;
		sp_char_exec(&parser, env);
		print_parser_struct(parser);
		function_listener(&parser, env, envp);
		if (g_last_signal != 0)
			update_env_status(env, g_last_signal);
		free_parser(&parser);
	}
}
