#include "../../includes/minishell.h"

/*(finished) Function is called when a char that normally the user wants to
target is incountered, it then get the index of the char c encountered at the string(line_read)
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

/*(finished) Count the number of char * present on the vector.*/
int count_arr_nb(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

/*
(finished) This function do a realloc between two arrays of char pointers
It will be on the sequence -> the first char ** will be at the
start and the second will be at the end.
*/
char **ft_realloc_two_lists(char **str, char **str_new)
{
	int		new_alloc;
	int		i;
	int		i_last;
	char	**new_arr;

	i = 0;
	i_last = 0;
	new_alloc = count_arr_nb(str) + count_arr_nb(str_new) + 1;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		free(str[i++]);
	}
	while (str_new[i_last] != NULL)
	{
		new_arr[i++] = ft_strdup(str_new[i_last]);
		free(str_new[i_last++]);
	}
	free(str);
	free(str_new);
	new_arr[i] = NULL;
	return (new_arr);
}

/*
(finished) This function do a realloc of an array of char pointers and puts a new
char pointer at the end of the array.
*/
char **ft_realloc_list_and_str(char **str, char *str_new)
{
	int		new_alloc;
	int		i;
	char 	**new_arr;

	i = 0;
	new_alloc = count_arr_nb(str) + 2;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str_new);
	new_arr[i + 1] = NULL;
	free(str_new);
	free(str);
	return new_arr;
}

/*
(incomplete) This function will pass through the line_readed and will count how many arguments will exist
(an argument is a word that is not between quotes or a sentence that is indeed between simple or double quotes.)
*/
int	count_args(char *line_read)
{
	int	count;
	int	i;

	i = 0;
	count = 0;

	/*Just to work - return will change*/
	(void)count;
	while(line_read[i] != '\0')
	{
		if (line_read[i+1])
		i++;
	}
	/*Just to work - return will change*/
	return (i);
}