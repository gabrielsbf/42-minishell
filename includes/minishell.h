/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:46:46 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/19 18:49:15 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
//readline lib
# include <readline/readline.h>
# include <readline/history.h>
//common libs
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
//system libs
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

extern int	g_last_signal;
typedef struct parsing
{
	char			*entire_text;
	char			*command_text;
	char			*main_command;
	char			*special_char;
	char			**exec_txt;
	char			**redir;
	char			**arguments;
	char			**env_path;
	int				fd_in;
	int				fd_out;
	int				fd_hdoc;
	int				status;
	int				pid;
	struct parsing	*next;
	struct parsing	*head;
}	t_parse;

typedef struct s_env
{
	char			*value;
	char			*name;
	struct s_env	*next;
	struct s_env	*head;
}	t_env;

typedef struct utils_prompt
{
	char	**actual_text;
	char	*path;
	int		count_args;
	int		input_num;
	int		number_of_inputs;

}	t_prompt;

//Parsing - srcs/parsing/
int		def_parse_lim(t_parse **parser);
int		get_redirect_part(t_parse **parser, char *cmd_txt, int mem);
char	**get_env_path(t_env **env);
int		get_next_match(char *line_read, int position, char c);
int		validate_line_read(char *line_read);
int		count_arr_nb(char **str);
void	parser_set(t_parse **parser, char *line_read, t_env **env, int i);
char	**ft_realloc_two_lists(char **str, char **str_new);
char	**ft_realloc_list_and_str(char **str, char *str_new);
int		set_main_command(t_parse **parser, char *line_read);
int		jump_special_char(char *line_read);
//TEXT UTILS
void	set_vars(char *ref, int *i, int *start, int final);
void	check_and_setvars(int *final, int *begin, char *ref, int proc);
int		is_quote(char c);
int		test_quote(char *line_read);
int		check_along(char *line_read, int i);
int		num_of_pipes(char *line_read);
int		is_btw_qts(char *line_read, int memory);
int		is_blank_substr(char *line_read, int memory, int pos);
int		is_spchar(char *stretch);
int		necessary_change(char *line_sub);
char	*join_str_val(char *init, char *end);
char	*inject_text(char **start, char **end, char *prefend, char *sufend);
void	inject_in_op(char **dst, char *ref, int *start, int *f_qt);
void	set_positions(char *ref, int *begin, int *last, int *start);
void	join_specific_quote(char **dst, char qt, int is_begin);
char	*exclude_spaces(char *line_sub);
void	exclude_quotes(char **argument);
char	*substr_val(char *s, int start, int final);
char	*join_quotes(char *line_sub);
int		split_process(t_parse **parser, int memory, int pos);
void	parsing_process(char **line_read, t_parse **parser, t_env **env);
t_parse	*main_line_process(char *line_read, t_env **env);
t_parse	*init_parse(char *line, char *cmd_str, t_parse *head, t_env **env);
int		pipe_char_pos(char *line_sub);
char	*separate_line_read(char *line_sub);
// ENV EXPANSION FUNC.
int		expansion_valid(char *text, int memory);
int		expand_variable(char **text, int i_cipher, t_env **envs);
void	env_and_quotes(t_parse **parser, char **text, t_env **envs);
void		replace_text(char **text, char *find, char *replace);
// void	hand_cipher(t_parse **parser, char *text, int argument, t_env **envs);
char	*check_name_in_env(t_env **envs, char *name);
//------Debug Function------ To Print
void	verify_env_head(t_env **env);
void	print_parser_struct(t_parse *parser);
//Env
void	update_env_status(t_env **env, int status);
void	add_env_status(t_env **env);
char	*check_name_in_env(t_env **envs, char *name);
char	*get_env_name(char **arg);
int		get_value_length(char **env);
char	*get_env_value(char **env);
int		is_env_available(char c);
t_env	*create_env_list(char **envp);
t_env	*add_env_node(char **env, t_env *head);
void	get_env(t_env **env, t_parse **parser);
void	free_env_node(t_env *env);

//ENV ON HEREDOC
void	replace_here(char **text_in, char *find, char *replace);
int		expand_heredoc(char **text_in, int i_cipher, t_env **envs);
int		here_valid_qt(char *text, int memory);
void	here_expansion(char **text, t_env **envs);
//prompt

char	*prompt_prefix(void);
void	server_loop(t_env **env, char **envp);
// srcs/prompt_set/built_ins/
void	ft_exit(t_parse **parser, t_env **env);
int		ft_echo(t_parse **parser);
int		pwd(t_parse **parser);
int		cd_manager(char *argument, t_env **env);
int		export_to_env(t_env **env, char **arguments);
void	unset_from_env(t_env **env, char **arguments);
void	function_listener(t_parse **parser, t_env **env, char **envp);
int		built_ins_manager(t_parse **parser, t_env **env);
void	pipe_built_ins(t_parse **parser, t_env **env, t_parse *head);
// free utils
void	free_str_arr(char **args);
void	free_env(t_env **env);
void	free_str(char **str);
void	free_parser_str(t_parse **parser);
void	free_parser(t_parse **parser);
// redirect
void	redirect(t_parse **parser, int redir_i);
void	append(t_parse **parser, int redir_i);
char	*get_redir_name(char	*redir);
void	redirect_in(t_env **env, t_parse **parser, int redir_i);
int		pipe_handler(t_parse **parser);
void	sp_char_exec(t_parse **parser, t_env **env);
void	read_heredoc(t_parse **parser, int redir_i, int fd, t_env **env);
void	heredoc_exec(t_parse **parser, int redir_i, t_env **env, t_parse *head);
//exit utils
void	sigquit_exit(t_env **env, t_parse **parser);
void	non_numeric_exit(t_env **env, t_parse **parser);
void	many_args_exit(t_env **env, t_parse **parser);

// exec
void	get_execargs(char *args, char **exec_arg, int arr_i);
void	create_execargs(t_parse **parser);
char	*create_path_exec(t_parse **parser);
int		get_arg_len(t_parse *parser);
void	execution(t_parse **parser, t_env **env, char **envp);
void	closing_fd(t_parse *parser);
// status
void	throw_error(int status);
//maybe libft
int		ft_strcmp(char const *str, char const *cmp);
int		ft_is_dir(char	*path);
int		check_slash(char *path);
char	*remove_slash(char *file);
#endif
