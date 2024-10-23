#include "../../includes/minishell.h"

/*make a validation on a stretch of a string to se if have validation special chars
special chars are:
* <
* >
* |

the '>' chars can be proceeded by one more char of the same:
* >>
* <<
return codes:
1. > or <
2. |
3. >> or <<

if results to 0 it means it's not a special char
*/
int		is_special_char(char *stretch)
{
	if ((stretch[0] == '>' || stretch[0] == '<') && stretch[0] == stretch[1])
		return (3);
	if (stretch[0] == '>' || stretch[0] == '<')
		return (1);
	if (stretch[0] == '|')
		return (2);
	return (0);
}

int		pipe_char_pos(char *line_sub)
{
	int	i;

	i = jump_special_char(line_sub);
	while (line_sub[i] != '\0')
	{
		if (is_special_char(&line_sub[i]) == 2 && !is_between_quotes(line_sub, i))
			return (i++);
		i++;
	}
	return (i);
}

char	*separate_line_read(char *line_sub)
{
	int index;

	index = pipe_char_pos(line_sub);
	if (line_sub[index] == '\0')
		return ft_substr(line_sub, 0, index);
	return ft_substr(line_sub, 0, index + 1);
}
