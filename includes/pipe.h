#ifndef PIPE_H
# define PIPE_H

typedef struct parsing
{
	char	*entire_text;
	char	*command_text;
	char	*main_command;
	char	**exec_txt;
	char	*special_char;
	char	*write_file;
	char	*read_file;
	char	**flags;
	char	**arguments;
	char	**env_path;
	int		fd_in;
	int		fd_out;
	int		is_error;
	int		pid;
	struct	parsing *next;
	struct	parsing *head;
}	t_parse;

typedef struct s_env
{
	char	*value;
	char	*name;
	struct	s_env *next;
	struct	s_env *head;
}	t_env;

typedef struct utils_prompt
{
	char	**actual_text;
	char	*path;
	int		count_args;
	int		input_num;
	int		number_of_inputs;

}	t_prompt;

// srcs/prompt_set/pipe_utils
//DEPRECATED - int			pipe_exec(int argc, char *argv[], t_prompt **prompt);
//DEPRECATED - void		simple_prompt_handler(int argc, char *argv[], t_prompt **t_prompt);

// srcs/prompt_set/prompt_set

//DEPRECATED -  void		free_str_in_pointer(char **string);
//DEPRECATED -  void		free_struct(t_prompt **prompt);
//DEPRECATED -  t_prompt	*init_prompt_struct(void);
//DEPRECATED -  int			count_prompt_args(t_prompt **prompt);

//Parsing - srcs/parsing/
// DEPRECATED - > char		*st_put_specialch(char **arguments);

//Parsing - srcs/parsing/

int			get_next_match(char *line_read, int position, char c);
int			validate_line_read(char *line_read);
int			count_arr_nb(char **str);
char		**ft_realloc_two_lists(char **str, char **str_new);
char		**ft_realloc_list_and_str(char **str, char *str_new);
int			count_args(char *line_read);
int			set_main_command(t_parse **parser, char *line_read);
int			jump_special_char(char *line_read);
int			is_between_quotes(char *line_read, int memory);
int			is_blank_substr(char *line_read, int memory, int pos);
int			is_special_char(char *stretch);
int			split_process(t_parse **parser, int memory, int pos);
void		parsing_process(char *line_read, t_parse **parser);
t_parse		*main_line_process(char *line_read, t_env **env);
t_parse		*init_parse(char *line_read, char *cmd_str, t_parse *head, t_env **env);


int			pipe_char_pos(char *line_sub);
char		*separate_line_read(char *line_sub);
// ENV EXPANSION FUNC.

int		expand_variable(t_parse **parser, int argument, int i_cipher, t_env **envs);
void	env_expansion(t_parse **parser, t_env **envs);
void	replace_text(t_parse **parser, int argument, char *find, char *replace);
void	hand_cipher(t_parse **parser, char *text, int argument, t_env **envs);
char *	check_name_in_env(t_env **envs, char * name);
//------Debug Function------ To Print

void	print_parser_struct(t_parse *parser);

//------Env------

char	*check_name_in_env(t_env **envs, char * name);
char	*get_env_name(char **env);
int		get_value_length(char **env);
char	*get_env_value(char **env);
int		is_env_available(char c);
t_env	*create_env_list(char **envp);
t_env	*add_env_node(char **env, t_env *head);
void	get_env(t_env **env, t_parse **parser);
void	free_env_node(t_env *env);

#endif
