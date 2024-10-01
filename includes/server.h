#ifndef SERVER_H
# define SERVER_H

char	*prompt_prefix(void);
void	server_loop(t_prompt **prompt_st, t_env **env);
// srcs/prompt_set/built_ins/
void	ft_echo(char **splitted_instructions);
void	ft_fork(void);
void	list_directory(const char *path);
void	pwd();
void	cd_manager(char *argument);
void	export_to_env(t_env **env, char **splitted_instructions);
void	unset_from_env(t_env **env, char **splitted_instructions);
void	function_listener(t_parse **parser, t_env **env);
void	get_signal();
#endif
