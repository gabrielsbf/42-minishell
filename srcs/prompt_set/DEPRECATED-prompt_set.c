#include "../../includes/minishell.h"

/*FILE DEPRECATED - NEED TO THINK ABOUT
t_prompt	*init_prompt_struct(void)
{
	t_prompt *prompt_cons;

	prompt_cons = malloc(sizeof(t_prompt));
	prompt_cons->number_of_inputs = 0;
	return (prompt_cons);
}

void	free_str_in_pointer(char **string)
{
	int i;

	i = 0;
	while (string[i] != NULL)
	{
		free(string[i]);
		i++;
	}
}

void	free_struct(t_prompt **prompt)
{
	free_str_in_pointer((*prompt)->actual_text);
	free((*prompt)->path);
	free(prompt);
}

int	count_prompt_args(t_prompt **prompt)
{
	int i;

	i = 0;
	while ((*prompt)->actual_text[i] != NULL)
		i++;
	return (i);
}

*/
