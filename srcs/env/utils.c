#include "../../includes/minishell.h"

/*FUNCTION THAT MAYBE CAN GO TO LIBFT
BASIC FIND AND REPLACE*/
void	replace_text(t_parse **parser, int arg, char *find, char *replace)
{
	char *text;
	int	new_alloc;
	int	i_old;
	int	i_new;

	i_old = 0;
	i_new = 0;
	new_alloc = ft_strlen((*parser)->arguments[arg]) - ft_strlen(find) + ft_strlen(replace) + 2;
	text = ft_strdup((*parser)->arguments[arg]);
	free((*parser)->arguments[arg]);
	(*parser)->arguments[arg] = (char *)malloc(new_alloc * sizeof(char));
	if ((*parser)->arguments[arg] == NULL)
		return ;
	while (text[i_old] != '\0')
	{
		if (text[i_old] == '$')
		{
			if (ft_strncmp(&text[i_old + 1], find, ft_strlen(find)) == 0)
			{
				ft_strlcpy(&(*parser)->arguments[arg][i_new], replace, ft_strlen(replace)+1);
				i_new = i_new + ft_strlen(replace);
				i_old = i_old + ft_strlen(find) + 1;
			}
		}
		if (text[i_old] != '\0')
		{
			(*parser)->arguments[arg][i_new] = text[i_old];
			i_old++;
			i_new++;
		}
	}
	(*parser)->arguments[arg][i_new] = '\0';
}

int	is_env_available(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
