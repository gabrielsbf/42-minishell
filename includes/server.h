#ifndef SERVER_H
#define SERVER_H

#include <readline/readline.h>
#include <readline/history.h>

char	*prompt_prefix(void);
void	server_loop(t_prompt **prompt_st);
// srcs/prompt_set/built_ins/
void	ft_echo(char **splitted_instructions);
void	ft_fork(void);
void	list_directory(const char *path);
void	pwd();
void	cd_manager(char *argument);
void	get_env();
void	function_listener(t_parse **parser);
#endif
