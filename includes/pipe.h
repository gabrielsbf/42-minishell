#ifndef PIPE_H
# define PIPE_H

#include<unistd.h>
#include<stdio.h>

typedef struct parsing
{
	char	*entire_text;
	char	*main_command;
	char	**flags;//n
	char	**arguments;
	char	*special_char;//n
	struct	parsing *next;

}	t_parse;

typedef struct s_env
{
	char	*value;
	char	*var;
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
int			pipe_exec(int argc, char *argv[], t_prompt **prompt);
void		simple_prompt_handler(int argc, char *argv[], t_prompt **t_prompt);

// srcs/prompt_set/prompt_set
void		free_str_in_pointer(char **string);
void		free_struct(t_prompt **prompt);
t_prompt	*init_prompt_struct(void);
int			count_prompt_args(t_prompt **prompt);

// ----- debug functions ----- maybe remove
void		print_text_input(char **splitted_instructions);
//Parsing - srcs/parsing/parser_set
int			get_next_match(char *line_read, int position, char c);
int			first_command_is_valid(char *line_read);
int			validate_line_read(char *line_read);
int			count_arr_nb(char **str);
char		**ft_realloc_two_lists(char **str, char **str_new);
char		**ft_realloc_list_and_str(char **str, char *str_new);
int			count_args(char *line_read);
int			set_main_command(t_parse **parser, char *line_read);
int			is_between_quotes(char *line_read, int memory, char find);
int			is_blank_substr(char *line_read, int memory, int pos);
int			split_process(t_parse **parser, int memory, int pos, char c);
void		parsing_process(char *line_read, t_parse **parser);
void		main_line_process(char *line_read);
t_parse		*init_parse(char *line_read);
//------Debug Function------ To Print
void	print_parser_struct(t_parse **parser);
#endif
