#include "../../includes/minishell.h"

int	readline_writed (char *line_read)
{
	if (ft_strcmp(line_read, "") == 0)
		return (0);
	return (1);
}

/*
Validates the quotes on line buffer.

every simple or double quote that starts needs to have a second to end.
.*/

int	test_quote (char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i] != '\0')
	{
		if ((line_read[i] == 34 || line_read[i] == 39))
			i = get_next_match(line_read, i, line_read[i]);
		if (i == -1)
			return (0);
		i++;
	}
	return (1);
}

int	check_along (char *line_read, int i)
{
	int back;

	back = i - 1;

	while (is_special_char(&line_read[back]) > 0 && back >= 0)
		back--;
	while (back >= 0 && ft_isspace(line_read[back]))
		back--;
	if (back < 0 && is_special_char(&line_read[i - 1]) == 1)
		return (is_special_char(&line_read[i - 1]));
	while (ft_isspace(line_read[i]) == 1)
		i++;
	if (line_read[i] == '\0')
		return (4);
	else
		return (is_special_char(&line_read[i]));
}

int	test_sp_char (char *line_read)
{
	int	valchar;
	int	i;

	valchar = 0;
	i = 0;
	while (line_read[i] != '\0')
	{
		if (is_between_quotes(line_read, i) != 0)
		{
			i++;
			continue;
		}
		if (is_special_char(&line_read[i]) >= 1 &&
		is_special_char(&line_read[i]) <= 2)
			valchar = check_along(line_read, i + 1);
		else if (is_special_char(&line_read[i]) == 3)
			valchar = check_along(line_read, i + 2);
		if (valchar != 0)
			return (-(valchar));
		i++;
	}
	return (1);
}

int	validate_line_read(char *line_read, t_env **env)
{
	(void)env;
	int	resp;
	printf("test quote is >> %d\n", test_quote(line_read));
	printf("test special char is >> %d\n", test_sp_char(line_read));
	printf("you write anything on the readline is >> %d\n", readline_writed(line_read));
	if (!readline_writed(line_read))
		return (0);
	if (test_quote(line_read) == 0)
		ft_putendl_fd("bash: syntax error near unexpected token `quotes'", 2);//status_handle
	else if (test_sp_char(line_read) < 0)
	{
		if (test_sp_char(line_read) == -2)
			ft_putendl_fd("bash: syntax error near unexpected token", 2);
		if (test_sp_char(line_read) == -1)
			ft_putendl_fd("bash: syntax error near unexpected token", 2);
		if (test_sp_char(line_read) == -3)
			ft_putendl_fd("bash: syntax error near unexpected token", 2);
		if (test_sp_char(line_read) == -4)
			ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
	}
	else
		return (1);
	return (0);

}

int	is_blank_substr(char *line_read, int memory, int pos)
{
	// printf("start function -> is blank substr\n");
	if (pos < memory)
		return (2);
	while (pos >= memory)
	{
		if (!ft_isspace(line_read[pos]) && line_read[pos] != '\0')
			return (0);
		pos--;
	}
	return (1);
}


/*
DEPRECATED FOR WHILE.
char	*st_put_specialch(char **arguments)//checar special char durante o processo de parsing
{
	int		i;
	char	*special_char;

	i = 0;
	if (!arguments)
		return NULL;
	special_char = NULL;
	while(arguments[i] != NULL)
	{
		if (ft_strcmp(arguments[i], ">>") == 0 || ft_strcmp(arguments[i], "<<") == 0)
		{
			special_char = ft_calloc(sizeof(char), 3);
			special_char = arguments[i];
		}
		else if (ft_strcmp(arguments[i], "<") == 0 || ft_strcmp(arguments[i], ">") == 0
			|| ft_strcmp(arguments[i], "|") == 0)
		{
			special_char = ft_calloc(sizeof(char), 2);
			special_char = arguments[i];
		}
		i++;
	}
	return (special_char);
}
*/
