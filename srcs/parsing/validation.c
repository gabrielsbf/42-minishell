#include "../../includes/minishell.h"

/*
(incomplete) Function to return 1 if the main command on the prompt is validated and 0 if not
 */
int	first_command_is_valid(char	*line_read)
{
	/*Just to work - return will change*/
	(void)line_read;

	return (1);
}

/*
(incomplete)Validates the line buffer.
Rules:
1. (already did) every simple or double quote that starts needs to have a second to end.
2. (still not did) the first command needs to be valid.
.*/
int	validate_line_read(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] != '\0')
	{
		if (line_read[i] == 34 || line_read[i] == 39)
		{
			i = get_next_match(line_read, i, line_read[i]);
		}
		if (i == -1)
			return (0);
		i++;
	}
	//printf("validate line read is OK\n");
	return (1);
}


int	is_between_quotes(char *line_read, int memory, char find)
{
	int	qt;
	//printf("testing in quotes\n");
	qt = 0;
	while (memory >= 0)
	{
		//printf("reverse getting memory -> char is: %c\n",line_read[memory]);
		if (line_read[memory] == find)
			qt++;
		memory--;
	}
	if (qt == 0 || qt % 2 == 0)
		return (0);
	return (1);
}

int	is_blank_substr(char *line_read, int memory, int pos)
{
	//printf("start function -> is blank substr\n");
	while (pos >= memory)
	{
		if (!ft_isspace(line_read[pos]) && line_read[pos] != '\0')
			return (0);
		pos--;
	}
	//printf("is blank substr\n");
	return (1);
}
