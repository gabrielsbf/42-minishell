#include "../../includes/minishell.h"

int		is_special_char(char *stretch)
{
	if (stretch[0] == '>' || stretch[0] == '<')
		return (1);
	if (stretch[0] == '|')
		return (2);
	return (0);
}

int		special_char_pos(char *line_sub)
{
	int	i;
	int	got_in;

	got_in = 0;
	i = 0;
	i = jump_special_char(line_sub);
	while (line_sub[i] != '\0')
	{
		while (is_special_char(&line_sub[i]) && !is_between_quotes(line_sub, i))
		{
			i++;
			got_in = 1;
			if (is_special_char(&line_sub[i - 1]) == 2)
				break;
		}
		if (got_in == 1)
			return (i - 1);
		i++;
	}
	return (i);
}

char	*separate_line_read(char *line_sub)
{
	int index;

	index = special_char_pos(line_sub);
	if (line_sub[index] == '\0')
		return ft_substr(line_sub, 0, special_char_pos(line_sub));
	return ft_substr(line_sub, 0, special_char_pos(line_sub) + 1);
}
