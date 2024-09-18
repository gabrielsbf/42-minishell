#include "../../includes/minishell.h"

void get_env(t_env **env)
{
	t_env *swap;

	swap = (*env);
	while (swap != NULL)
	{
		printf("%s=%s\n", swap->name, swap->value);
		swap = swap->next;
	}
}
