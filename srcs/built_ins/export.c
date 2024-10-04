#include "../../includes/minishell.h"

int	export_error(char **splitted_instructions)
{
	int	i;

	i = 0;
	while (splitted_instructions[0][i] != '\0')
	{
		if (splitted_instructions[0][i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_to_env(t_env **env, char **splitted_instructions)
{
	t_env *swap;

	swap = (*env);
	if (!*splitted_instructions || export_error(splitted_instructions) == 0)
	{
		ft_putstr_fd("EXPORT ERROR", 2);
		return ;
	}
	while (swap->next != NULL)
	{
		if (ft_strcmp(swap->name, get_env_name(splitted_instructions)) == 0)
		{
			swap->value = get_env_value(splitted_instructions);
			break ;
		}
		swap = swap->next;
	}
	if (ft_strcmp(swap->name, get_env_name(splitted_instructions)) == 0)
		swap->value = get_env_value(splitted_instructions);
	else
		swap->next = add_env_node(splitted_instructions, (*env));
	if (swap->head != NULL)
		swap = swap->head;
	(*env) = swap;
}
