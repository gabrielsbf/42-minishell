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

/*
If
RETURNS:
* either 34 or 39 which means what quote the char is between
* either 68(34 * 2) or 78(39 * 2) which means that the char is
* 0 if it's not between quotes
*/
// static int	determine_cases(int d_open, int s_open, int last, char *ptr_to_mem)
// {
// 	int	i;
// 	int res;
// 	i = 0;
// 	if (*ptr_to_mem == 34 || *ptr_to_mem == 39)
// 	{
// 		if (*ptr_to_mem == 34 && d_open)
// 	}

// 	if (d_open == 1 && s_open == 1)
// 	{
// 		if (last == 34 && *ptr_to_mem == 34)
// 			return (68);
// 		else if (last == 34)
// 			return (34);
// 		else if (last == 39 && *ptr_to_mem == 39)
// 			return (78);
// 		else if (last == 39)
// 			return (39);
// 	}
// 	if (d_open == 1)

// 	return (0);
// }

int	is_between_quotes(char *line_read, int mem)
{
	int iter;
	int prior;
	int lock;

	iter = 0;
	prior = 0;
	lock = 0;
	// printf("testing in quotes\nline read: %s, mem: %d, line read em mem: %d\n", line_read, mem, line_read[mem]);
	while (iter <= mem)
	{
		// printf("char is: %d\n", line_read[iter]);
		if ((line_read[iter] == 39 || line_read[iter] == 34) && lock == 0)
		{
			prior = line_read[iter];
			lock = 1;
		}
		else if (line_read[iter] == prior)
		{
			// printf("prior returned to zero\n");
			lock = 0;
			prior = 0;
		}
		iter++;
	}
	// printf("prior in this situation is: %d\n", prior);
	if (prior == 0 && (line_read[mem] == 34 || line_read[mem] == 39))
		return (line_read[mem] * 2);
	else
		return (prior);
}

int	is_blank_substr(char *line_read, int memory, int pos)
{
	// printf("start function -> is blank substr\n");
	while (pos >= memory)
	{
		if (!ft_isspace(line_read[pos]) && line_read[pos] != '\0')
			return (0);
		pos--;
	}
	//printf("is blank substr\n");
	return (1);
}
