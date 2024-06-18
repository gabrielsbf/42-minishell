#include "../../includes/minishell.h"

char *prompt_prefix(void)
{
	char    *prompt_prefix;
	char    *temp;

	prompt_prefix = ft_strjoin(getenv("LOGNAME"), "@");
	temp = ft_strjoin(prompt_prefix, getenv("NAME"));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, ":");
	free(temp);
	temp = ft_strjoin(prompt_prefix, getenv("PWD"));
	free(prompt_prefix);
	prompt_prefix = ft_strjoin(temp, "$ ");
	return (prompt_prefix);
}

void	free_prompt_el(char *prefix, char *line_read)
{
	free(line_read);
	free(prefix);
}

void    server_loop(t_prompt **prompt_st)
{
	(void)prompt_st;
	char    *line_read;
	char	*prefix_element;
	while (1)
	{
		prefix_element = prompt_prefix();
		line_read = readline(prefix_element);
		printf("%s", line_read);
		free_prompt_el(prefix_element, line_read);
	}
}
