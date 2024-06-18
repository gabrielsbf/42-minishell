#include "../includes/minishell.h"

int main(int argc, char *argv[])
{
	t_prompt *prompt_in;
	
	prompt_in = init_prompt_struct();
	server_loop(&prompt_in);
	return (0);
}