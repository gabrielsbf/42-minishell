#include "../../includes/minishell.h"

int	ft_strcmp(char const *str, char const *cmp)
{
	int	i;

	i = 0;
	while ((str[i] != '\0' && cmp[i] != '\0') && str[i] == cmp[i])
		i++;
	return (str[i]-cmp[i]);
}
