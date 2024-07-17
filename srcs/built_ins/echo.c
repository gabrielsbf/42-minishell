#include "../../includes/minishell.h"

void	ft_echo(char **splitted_instructions)
{
	int i;
	int trailing;

	// printf("in echo, arg 0 is : %s\n", splitted_instructions[0]);
	trailing = 0;
	i = 0;
	if (ft_strncmp(splitted_instructions[0], "-n", 3) == 0)
		i++;
	else
		trailing = 1;
	while (splitted_instructions[i] != NULL)
	{
		printf("%s", splitted_instructions[i]);
		if (splitted_instructions[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (trailing == 1)
		printf("\n");
}
