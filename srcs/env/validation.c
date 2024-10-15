#include "../../includes/minishell.h"

char *	check_name_in_env(t_env **envs, char * name)
{
	t_env *swap;

	swap = (*envs);
	while (swap != NULL)
	{
		if (ft_strncmp(swap->name, name, ft_strlen(name) + 1) == 0)
			break;
		swap = swap->next;
	}
	if (swap == NULL)
		return (NULL);
	return (swap->value);
}
