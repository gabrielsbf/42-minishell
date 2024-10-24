#ifndef SERVER_H
# define SERVER_H

char	*prompt_prefix(void);
void	server_loop(t_env **env, char **envp);
// srcs/prompt_set/built_ins/
void	ft_exit(t_parse **parser, t_env **env);
void	ft_echo(t_parse **parser);
void	ft_fork(void);
void	pwd(t_parse **parser);
void	cd_manager(char *argument, t_env **env);
void	export_to_env(t_env **env, char **splitted_instructions);
void	unset_from_env(t_env **env, char **splitted_instructions);
void	function_listener(t_parse **parser, t_env **env, char **envp);
// free utils
void	free_str_arr(char **args);
void	free_env(t_env **env);
void	free_str_arr(char **args);
void	free_parser_str(t_parse *parser);
void	free_parser(t_parse **parser);
// redirect
void	redirect(t_parse **parser);
int	append(t_parse **parser);
int	pipe_handler(t_parse **parser);
void sp_char_exec(t_parse **parser, t_env **env, char **envp);
//exit utils
void	sigquit_exit(t_env **env, t_parse **parser);
void	non_numeric_exit(t_env **env, t_parse **parser);
void	many_args_exit(t_env **env, t_parse **parser);

// exec
int	get_arg_len(t_parse *parser);
int execution(t_parse **parser, char **envp);
#endif
