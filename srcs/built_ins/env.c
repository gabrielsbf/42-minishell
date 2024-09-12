#include "../../includes/minishell.h"

void get_env(t_env **env)
{
	t_env *swap;

	while ((*env))
	{
		if ((*env)->next == NULL)
			swap = (*env)->head;
		printf("%s=%s\n", (*env)->name, (*env)->value);
		(*env) = (*env)->next;
	}
	(*env) = swap;
}
