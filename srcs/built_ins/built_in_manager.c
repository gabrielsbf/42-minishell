#include "../../includes/minishell.h"

void	function_listener(char **splitted_instructions)
{
	int	i;

	i = 0;
	while (splitted_instructions[i] != NULL)
	{
		if (ft_strncmp(splitted_instructions[i], "echo", 4) == 0)
			echo (splitted_instructions);
		else if (ft_strncmp(splitted_instructions[i], "fork", 4) == 0)
			ft_fork ();
		else if (ft_strncmp(splitted_instructions[i], "exit", 4) == 0)
			exit(0);
		i++;
	}
}
