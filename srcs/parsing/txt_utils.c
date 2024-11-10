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
// static	void put_std_quote(char **sentence)
// {
// 	char	*txt;
// 	char	*temp;

// 	txt = ft_strjoin("\"",*sentence);
// 	temp = ft_strjoin(txt, "\"");
// 	free(*sentence);
// 	*sentence = NULL;
// 	*sentence = ft_strdup(temp);
// }

char *join_str_val(char *init, char *end)
{
	if (init == NULL && end == NULL)
		return NULL;
	else if (init == NULL)
		return ft_strdup(end);
	else if (end == NULL)
		return ft_strdup(init);
	else
		return ft_strjoin(init, end);

}

char	*inject_text(char **line_start, char **line_end, char *prefix, char *sufix)
{
	char	*result;
	char	*end_complete;
	char	*pre_complete;

	result = NULL;
	end_complete = NULL;
	pre_complete = join_str_val(*line_start, prefix);
	end_complete = join_str_val(*line_end, sufix);
	result = join_str_val(pre_complete, end_complete);
	free_str(&pre_complete);
	free_str(&end_complete);
	free_str(line_start);
	free_str(line_end);
	*line_end = NULL;
	*line_start = NULL;
	pre_complete = NULL;
	end_complete = NULL;
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
	if (final >= (int)ft_strlen(ref))
	{
		*i = ft_strlen(ref);
		*start = *i;
	}
	else
	{
		*i = final;
		if (is_special_char(&ref[(*i)]) > 0)
			*i = *i;
		else if (ref[*i] != '\0' && is_special_char(&ref[(*i) + 1]) > 0)
			(*i) = (*i) + 1;
	}
	*start = *i;
	while(ref[*i] != '\0' && is_special_char(&ref[(*i) + 1]) > 0)
		(*i) = (*i) + 1;
	printf("i agora é >> %d, e start é %d\n", *i, *start);
}

void	check_and_setvars(int *final, int *begin, char *ref, int proc)
{
	int	i;

	i = 0;
	if (proc == 1)
	{
		if (*begin > 0 &&
				is_special_char(&ref[(*begin) - 1]) == 0)
			(*begin) = (*begin) - 1;
		if (ref[*final] != '\0' &&
				is_special_char(&ref[(*final) + 1]) == 0)
			(*final) = (*final) + 1;
	}
	else if(proc == 0)
	{
		i =	get_next_match(ref, *final, ref[(*final)]);
		if (i < 0 && is_quote(ref[(*final)]))
			(*final) = (*final) + 1;
	}
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
		*dst = inject_text(dst, &temp, NULL, NULL);
	}
	*start = *start + *f_qt;
}

void	join_specific_quote(char **dst, char	qt, int is_begin)
{
	char	*c;
	char	*copy;

	copy = ft_strdup(*dst);
	c = ft_calloc(sizeof(char), 2);
	c[0] = qt;
	free_str(dst);
	if (is_begin == 1)
		*dst = join_str_val(c, copy);
	else
		*dst = join_str_val(copy, c);
	free_str(&copy);
	free_str(&c);
}

void	pre_quote(char *ref, char **dst, int *i, int *start)
{
	char	*temp;
	char	quote;
	int		begin;
	int		sub;

	begin = *i;
	temp = NULL;
	quote = ref[begin];
	while (!ft_isspace(ref[begin]) && !is_special_char(&ref[begin]) && begin >= 0)
		begin--;
	if (begin < 0)
		sub = 0;
	else
		sub = begin + 1;
	temp = substr_val(ref, *start, sub);
	*dst = inject_text(dst, &temp, NULL, NULL);
	join_specific_quote(dst, quote, 0);
	(void)quote;
	free_str(&temp);
	*start = sub;
}

void	quote_op(char *ref, char **dst, int *f_qt, int *start)
{
	int		begin;
	int		l_qt;
	int		last;
	char	*temp;
	int		inc;

	inc = ref[*f_qt];
	while ((ref[*f_qt] == 34 || ref[*f_qt] == 39))
	{
		printf("STARTING LOOP\n");
		inject_in_op(dst, ref, start, f_qt);
		temp = NULL;
		begin = *f_qt;
		l_qt = get_next_match(ref, *f_qt, ref[(*f_qt)]);
		last = l_qt;
		check_and_setvars(&last, &begin, ref, 1);
		while (begin >= 0 && begin > *start && !ft_isspace(ref[begin]) &&
		!is_quote(ref[begin]) && is_special_char(&ref[begin]) == 0)
			begin--;
		if (begin == -1)
			begin++;
		while (ref[last] != '\0' && !ft_isspace(ref[last]) && !is_quote(ref[last]) &&
		is_special_char(&ref[last]) == 0)
			last++;
		temp = substr_val(ref, begin , (*f_qt) - 1);
		printf("First temp is %s\n", temp);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		printf("Second temp is %s\n", temp);
		temp = substr_val(ref, (*f_qt) + 1, l_qt);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		temp = substr_val(ref, l_qt + 1, last);
		printf("Third temp is %s\n", temp);
		(*dst) = inject_text(dst, &temp, NULL, NULL);
		check_and_setvars(&last, f_qt, ref, 0);
		set_vars(ref, f_qt, start, last);
		printf("LOOP ENDED\n\n");
	}
	if (inc == 34 || inc == 39)
		join_specific_quote(dst, inc, 0);
}

/*Still not decided what to do with that*/

// static void put_quotes_std(char **line_return, char *line_sub, int *start, int *i)
// {
// 	while ()
// 	char *ptr = substr_val(*line_return, *start, *i);
// 	printf("mem -> %d | final -> %d\n", mem, *final);
// 	printf("put quotes std >> %s\n", ptr);
// 	free_str(&ptr);

// }

char	*exclude_spaces(char *line_sub)
{
	char	*line_return;
	char	*temp_line;
	int		i;
	int		start;

	i = 0;
	start = 0;
	line_return = NULL;
	while (line_sub[i] != '\0')
	{
		while ((!ft_isspace(line_sub[i]) || is_between_quotes(line_sub, i)) &&
		line_sub[i] != '\0')
			i++;
		if (i != start)
		{
			if (line_sub[i] == '\0')
				temp_line = substr_val(line_sub, start, i);
			else
				temp_line = substr_val(line_sub, start, i + 1);
			line_return = inject_text(&line_return, &temp_line, NULL, NULL);
			start = i;
		}
		if (line_sub[i] == '\0')
			break;
		i++;
		start++;
	}
	if (i != start)
		temp_line = substr_val(line_sub, start, i);
	line_return = inject_text(&line_return, &temp_line, NULL, NULL);
	return line_return;
}



char	*join_quotes(char *line_pre)
{
	char	*line_return;
	char	*line_sub;
	char	*temp_line;
	int		i;
	int		start;

	temp_line = NULL;
	line_return = NULL;
	line_sub = exclude_spaces(line_pre);
	i = 0;
	start = 0;
	if (necessary_change(line_sub) == 0)
		return ft_strdup(line_sub);
	while (line_sub[i] != '\0')
	{
		if (line_sub[i] == 34 || line_sub[i] == 39)
			pre_quote(line_sub, &line_return, &i, &start);
		quote_op(line_sub, &line_return, &i, &start);
		if (line_sub[i] == '\0')
			break;
		i++;
	}
	temp_line = substr_val(line_sub, start, i);
	line_return = inject_text(&line_return, &temp_line, NULL, NULL);
	return (line_return);
}

