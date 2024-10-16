#include "../../includes/minishell.h"


/*
If
RETURNS:
* either 34 or 39 which means what quote the char is between
* either 68(34 * 2) or 78(39 * 2) which means that the char is
* 0 if it's not between quotes
*/
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

/*(finished) Function is called when a char that normally the user wants to
target is encountered, it then get the index of the char c encountered at the string(line_read)
the position argument set where is the index of the string that you want to begin.
The return is the absolute index of the position of the encountered char*/
int	get_next_match(char  *line_read, int position, char c)
{
	position++;
	while (line_read[position] != '\0' && line_read[position] != c)
		position++;
	if (line_read[position] != c)
		return -1;
	return position;

}
