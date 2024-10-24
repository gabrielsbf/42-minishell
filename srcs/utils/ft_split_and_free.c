#include "../../includes/minishell.h"

char	**ft_split_and_free(char *s, char c)
{
	char	**new_s;

	new_s = ft_split(s, c);
	free(s);
	return (new_s);
}
