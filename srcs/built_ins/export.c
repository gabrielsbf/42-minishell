#include "../../includes/minishell.h"

int	export_error(char *arguments)
{
	int	i;
	int	index;
	
	index = 0;
	i = 0;
	while (arguments[i] != '\0')
	{
		if (arguments[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_to_env(t_env **env, char **arguments)
{
	t_env *swap;
	int	iarg;

	iarg = 0;
	swap = (*env);
	while ((arguments[iarg] != NULL))
	{
		if (!arguments[iarg] || export_error(arguments[iarg]) == 0)
		{
			iarg++;	
			continue;
		}
		while (swap->next != NULL)
		{
			if (ft_strcmp(swap->name, get_env_name(&arguments[iarg])) == 0)
			{
				swap->value = get_env_value(&arguments[iarg]);
				break ;
			}
			swap = swap->next;
		}
		if (ft_strcmp(swap->name, get_env_name(&arguments[iarg])) == 0)
			swap->value = get_env_value(&arguments[iarg]);
		else
			swap->next = add_env_node(&arguments[iarg], (*env));
		if (swap->head != NULL)
			swap = swap->head;
		(*env) = swap;
		iarg++;
	}
}
