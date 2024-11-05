#include "../../includes/minishell.h"

int	export_error(char *arguments)
{
	int	i;

	i = 0;
	if (ft_isalpha(arguments[0]) == 0 && arguments[0] != '_')
		return (0);
	while (arguments[i] != '\0')
	{
		if (arguments[i] == '=')
			return (1);
		if (ft_isalnum(arguments[i]) == 0 && arguments[i] != '_')
			return (0);
		i++;
	}
	return (0);
}

t_env	*add_export(t_env **env, char **arguments)
{
	t_env	*export;
	t_env	*status;
	t_env	*temp;

	temp = (*env);
	while (ft_strcmp(temp->name, "?") != 0)
		temp = temp->next;
	status = temp;
	export = ft_calloc(sizeof(t_env), 1);
	export->head = temp->head;
	export->next = status;
	export->name = get_env_name(arguments);
	export->value = get_env_value(arguments);
	return (export);
}

int	is_export_updated(t_env *env, char	**arguments)
{
	while (env && ft_strcmp(env->next->name, "?") != 0)
	{
		if (ft_strcmp(env->name, get_env_name(arguments)) == 0)
		{
			env->value = get_env_value(arguments);
			return (1);
		}
		env = env->next;
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
		if (!arguments[iarg] || export_error(arguments[iarg]) == 0
		|| is_export_updated(swap, &arguments[iarg]) == 1)
		{
			iarg++;
			continue;
		}
		while (ft_strcmp(swap->next->name, "?") != 0)
			swap = swap->next;
		swap->next = add_export(env, &arguments[iarg]);
		iarg++;
	}
}
