#include "../../includes/minishell.h"

void	init_parser_struct(t_parse **parser)
{

}

int	get_next_quote_match(char  *trim_line_read, int position, char c)
{
	position++;
	while (trim_line_read[position] != '\0' && trim_line_read[position] != c)
		position++;
	if (trim_line_read[position] != c)
		return -1;
	return position;

}

/*
Building - Function to return 1 if the main command on the prompt is validated and 0 if not
 */
int	first_command_is_valid(char	*trim_line_read)
{
	return (1);
}

int	validate_line_read(char *trim_line_read)
{
	int	i;

	i = 0;
	while (trim_line_read[i] != '\0')
	{
		if (trim_line_read[i] == 34 || trim_line_read[i] == 39)
		{
			i = get_next_quote_match(trim_line_read, i, trim_line_read[i]);
		}
		if (i == -1)
			return (0);
		i++;
	}
	return (1);
}

int count_arr_nb(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

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
		free(str_new[i_last]);
		i_last++;
	}
	free(str);
	free(str_new);
	new_arr[i] = NULL;
	return (new_arr);
}

char **ft_realloc_list_and_str(char **str, char *str_new)
{
	int		new_alloc;
	int		i;
	char 	**new_arr;

	i = 0;
	new_alloc = count_prompt_args(str) + 2;
	new_arr = (char **)malloc(new_alloc * sizeof(char *));
	while (str[i] != NULL)
	{
		new_arr[i] = ft_strdup(str[i]);
		free(str[i]);
		i++;
	}
	new_arr[i] = str_new;
	free(str);
	return new_arr;
}

int	count_args(char *trim_line_read)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while(trim_line_read[i] != '\0')
	{
		if (trim_line_read[i+1])
		i++;
	}
}

/*---Parei aqui.
-----Preciso validar parte da leitura em cima do texto da esquerda pra direita.---*/
char *handle_line_read(char *line_read)
{
	char *get_line_treated;
	int	mall_count;


	get_line_treated = ft_strtrim(line_read, " ");
	free(line_read);
	if (!validate_line_read(get_line_treated))
		return (NULL);
}


t_parse	set_parse(char *line_read)
{
	t_parse	*parser;


}
