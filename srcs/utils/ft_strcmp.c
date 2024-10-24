#include "../../includes/minishell.h"

int	ft_strcmp(char const *str, char const *cmp)
{
	int	i;

	i = 0;
	while (str[i] == cmp[i] && (str[i] != '\0' && cmp[i] != '\0'))
		i++;
	return (str[i]-cmp[i]);
}
