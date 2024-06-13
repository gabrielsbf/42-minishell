#include "../../includes/minishell.h"

void    simple_prompt_handler(int argc, char *argv[], t_prompt **prompt)
{
    int     i;

    i = 0;
    (* prompt)->actual_text = (char **)malloc(sizeof(char *) * argc);
    while ((argc - 1) > i)
    {
        (* prompt)->actual_text[i] = ft_strdup(argv[i + 1]);
       i++;
    }
    (* prompt)->actual_text[i] = NULL;
    (* prompt)->path = ft_strjoin(FOLDER_BUILT_IN, (* prompt)->actual_text[0]);
    (* prompt)->count_args = count_prompt_input(prompt);
}

int pipe_exec(int argc, char *argv[], t_prompt **prompt)
{
    char *envp[] = {NULL};

    simple_prompt_handler(argc, argv, prompt);
    // printf("prompt path is : %s\n\n", (*prompt)->path);
    // printf("args are >>\n");
    // print_text_input(prompt);
    if (execve((*prompt)->path, (*prompt)->actual_text, envp) == -1)
    {    
        perror("command could not be executed.");
        free_struct(prompt);
    }
    return (1);
}

int main(int argc, char *argv[])
{
    t_prompt *prompt_in;
    
    prompt_in = prompt_init();
    pipe_exec(argc, argv, &prompt_in);
    return (0);
}