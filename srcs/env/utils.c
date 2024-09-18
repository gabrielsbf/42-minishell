#include "../../includes/minishell.h"

/*FUNCTION THAT MAYBE CAN GO TO LIBFT
BASIC FIND AND REPLACE*/
void	replace_text(char *entire_text, char *find, char *replace)
{
	char *text;
	int	new_alloc;
	int	i_old;
	int	i_new;

	i_old = 0;
	i_new = 0;
	new_alloc = ft_strlen(entire_text) - ft_strlen(find) + ft_strlen(replace) + 2;
	text = ft_strdup((entire_text));
	free(entire_text);
	(entire_text) = (char *)malloc(new_alloc * sizeof(char));
	if (entire_text == NULL)
		return ;
	while (text[i_old] != '\0')
	{
		if (text[i_old] == '$')
		{
			if (ft_strncmp(text[i_old + 1], find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(entire_text, replace, ft_strlen(replace)+1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
			}
		}
		if (text[i_old] != '\0')
		{
			entire_text[i_new] = text[i_old];
			i_old++;
			i_new++;
		}
	}
	entire_text[i_new] = '\0';
}

/*FUNCTION THAT MAYBE CAN GO TO LIBFT
IT CONSIDER A NEW MEMORY BLOCK THAT NEED TO GET FREE AND CREATE ANOTHER.
ALSO ALLOCS IN THE PAST VARIABLE*/

