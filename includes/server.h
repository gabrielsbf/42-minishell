#ifndef SERVER_H
#define SERVER_H

#include <readline/readline.h>
#include <readline/history.h>

char    *prompt_prefix(void);
void	free_prompt_el(char *prefix, char *line_read);
void	server_loop(t_prompt **prompt_st);
void	function_listener(char **splitted_instructions);
void	echo(char **splitted_instructions);
void	ft_fork();

#endif
