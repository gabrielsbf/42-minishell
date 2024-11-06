#include "../../includes/minishell.h"


int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}
/*
If
RETURNS:
* either 34 or 39 which means what quote the char is between
* either 68(34 * 2) or 78(39 * 2) which means that the char is quote and
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

/*Verify if it is necessary to make a change on the quotes part.*/
int	necessary_change(char *line_sub)
{
	int	i;

	i = 0;
	while (line_sub[i] != '\0')
	{
		if (line_sub[i] == 34 || line_sub[i] == 39)
		{
			i = get_next_match(line_sub, i, line_sub[i]);
			if (!ft_isspace(line_sub[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

/*if begin is 1 -> execute function with the first quote who appears
var need -> if really needs to make te input */
static	void put_std_quote(char **sentence, int begin, int	need)
{
	int	i;

	i = 0;
	if (need == 0)
		return ;
	if ((*sentence) == NULL)
		return ;
	if (begin == 1)
	{
		while ((*sentence)[i] != '\0')
		{
			if ((*sentence)[i] == 34 || (*sentence)[i] == 39)
			{
				(*sentence)[i] = 34;
				break;
			}
			i++;
		}
		return ;
	}
	else
		(*sentence)[ft_strlen((*sentence)) - 1] = 34;
}

char	*inject_text(char **line_start, char **line_end, int need_qt)
{
	char	*result;

	printf("entering inject text: linestart:%s | line_end: %s\n", (*line_start), (*line_end));
	if (*line_end == NULL)
		return (*line_start);
	put_std_quote(line_start, 1, need_qt);
	if (*line_start == NULL)
	{
		put_std_quote(line_end, 1, need_qt);
		result = ft_strjoin("", (*line_end));
	}
	else
	{
		put_std_quote(line_end, 0, need_qt);
		result = ft_strjoin(*line_start, *line_end);
		free(*line_start);
	}
	free(*line_end);
	*line_start = NULL;
	*line_end = NULL;
	return (result);
}

char	*substr_val(char *s, int start, int final)
{
	if (start >= final)
		return (NULL);
	return (ft_substr(s, start, final - start));
}

void		set_vars(char *ref, int *i, int *start, int final)
{
	if (ref[final] == '\0')
		*i = final;
	else
		*i = final;
	*start = *i;
}

void		inject_in_op(char **dst, char *ref, int *start, int *f_qt)
{
	char	*temp;

	temp = NULL;
	if (*dst == NULL)
		*dst = substr_val(ref, *start, *f_qt);
	else
	{
		temp = substr_val(ref, *start, *f_qt);
		*dst = inject_text(dst, &temp, 0);
	}
	*start = *start + *f_qt;
}
void	quote_op(char *ref, char **dst, int *f_qt, int *start)
{
	int		begin;
	int		l_qt;
	int		last;
	char	*temp;

	inject_in_op(dst, ref, start, f_qt);
	temp = NULL;
	begin = (*f_qt) - 1;
	l_qt = get_next_match(ref, *f_qt, ref[(*f_qt)]);
	last = l_qt + 1;
	while (begin >= 0 && begin > *start && !ft_isspace(ref[begin]) && !is_quote(ref[begin]))
		begin--;
	if (begin == -1)
		begin++;
	while (ref[last] != '\0' && !ft_isspace(ref[last]) && !is_quote(ref[last]))
		last++;
	temp = substr_val(ref, begin , (*f_qt) - 1);
	// printf("temp 1 : begin %d | f_quote %d\n", begin, *f_qt);
	(*dst) = inject_text(dst, &temp, 0);
	temp = substr_val(ref, (*f_qt) + 1, l_qt);
	// printf("temp 2 : f_quote %d | l_quote %d\n", *f_qt, l_qt);
	(*dst) = inject_text(dst, &temp, 0);
	temp = substr_val(ref, l_qt + 1, last);
	// printf("temp 3 : l_quote %d | final %d\n", l_qt, last);
	(*dst) = inject_text(dst, &temp, 0);
	set_vars(ref, f_qt, start, last);
}

char	*join_quotes(char *line_sub)
{
	char	*line_return;
	char	*temp_line;
	int		i;
	int		start;
	// int		incidence;

	line_return = NULL;
	i = 0;
	start = 0;
	// incidence = 0;
	if (necessary_change(line_sub) == 0)
		return ft_strdup(line_sub);
	while (line_sub[i] != '\0')
	{
		while ((line_sub[i] == 34 || line_sub[i] == 39))
		{
			quote_op(line_sub, &line_return, &i, &start);
			// incidence ++;
		}
		if (line_sub[i] == '\0')
			break;
		i++;
	}
	temp_line = ft_substr(line_sub, start, i - start);
	line_return = inject_text(&line_return, &temp_line, 0);
	printf("final line return is: %s\n", line_return);
	return (line_return);
}

/*
		while (line_sub[i] == 34 || line_sub[i] == 39)
		{
			printf("passing while line sub, char match is: %d\n", line_sub[i]);
			i = get_next_match(line_sub, i, line_sub[i]);
			printf("getnextmatch result is: %d\n", i);
			if (line_sub[i + 1] == 34 || line_sub[i + 1] == 39)
			{
				printf("quote condition is true!\n");
				temp_line = ft_substr(line_sub, start, i - start);
				i = i + 1;
				start = i + 1;
				line_return = inject_text(&line_return, &temp_line);
			}
			else
				i++;
				*/
