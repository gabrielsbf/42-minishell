#ifndef SERVER_H
# define SERVER_H

char	*prompt_prefix(void);
void	server_loop(t_env **env, char **envp);
// srcs/prompt_set/built_ins/
void	ft_echo(t_parse **parser);
void	ft_fork(void);
void	list_directory(const char *path);
void	pwd();
void	cd_manager(char *argument, t_env **env);
void	export_to_env(t_env **env, char **splitted_instructions);
void	unset_from_env(t_env **env, char **splitted_instructions);
void	function_listener(t_parse **parser, t_env **env, char **envp);
// redirect
void	redirect(t_parse **parser);
int	append(t_parse **parser);
int	pipe_handler(t_parse **parser);
int sp_char_exec(t_parse **parser, t_env **env, char **envp);
// exec
int execution(t_parse **parser, char **envp);
#endif
