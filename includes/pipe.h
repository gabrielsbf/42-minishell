#ifndef PIPE_H
# define PIPE_H

#include<unistd.h>
#include<stdio.h>

typedef struct utils_prompt
{
	char	**actual_text;
	char	*path;
	int		count_args;
	int		entered_time;

} t_prompt;
// srcs/prompt_set/pipe_utils
int			pipe_exec(int argc, char *argv[], t_prompt **prompt);
void    	simple_prompt_handler(int argc, char *argv[], t_prompt **t_prompt);

// srcs/prompt_set/struct_set
void		free_str_in_pointer(char **string);
void	    free_struct(t_prompt **prompt);
t_prompt	*prompt_init(void);
int			count_prompt_input(t_prompt **prompt);
// ----- debug functions ----- maybe remove
void		print_text_input(t_prompt **prompt);

// srcs/prompt_set/built_ins/echo.c
void    echo(char *argv[]);
#endif