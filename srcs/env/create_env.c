#include "../../includes/minishell.h"

char	*get_env_name(char **env)
{
	int	i;
	char	*name;

	i = 0;
	while (env[0][i] != '\0' && env[0][i] != '=')
		i++;
	//printf("%i\n", i);
	name = ft_calloc(sizeof(char), (i + 1));
	if (!name)
		return (NULL);
	while (i-- > 0)
		name[i] = env[0][i];
	//printf("%s\n", name);
	return name;
}

int	get_value_length(char **env)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (env[0][i] != '\0' && env[0][i] != '=')
		i++;
	while (env[0][i++] != '\0')
	{
		//printf("%c", env[0][i]);
		length++;
	}
	//printf("\n%i", length);
	return (length);
}

char	*get_env_value(char **env)
{
	int	i;
	int	value_i;
	char	*value;

	i = 0;
	value_i = -1;
	while (env[0][i] != '\0' && env[0][i] != '=')
		i++;
	//printf("%i\n", value_length);
	value = ft_calloc (sizeof(char), (get_value_length(env) + 1));
	if (!value)
		return (NULL);
	while (env[0][i] != '\0' && env[0][i] != '=')
		value[++value_i] = env[0][++i];
	//printf("%s\n", value);
	return value;
}

t_env	*add_env_node(char **env, t_env *head)
{
	t_env	*env_node;
	env_node = ft_calloc(sizeof(t_env), 1);
	env_node->head = head;
	env_node->name = get_env_name(env);
	env_node->value = get_env_value(env);

	return env_node;
}

t_env	*create_env_list()
{
	char	**env;
	t_env	*env_list;
	t_env	*head;

	env = __environ;
	head = NULL;
	env_list = add_env_node(env, head);
	while(*++env)
	{
		if (!head)
			head = env_list;
		env_list->next = add_env_node(env, head);
		env_list = env_list->next;
	}
	env_list->next = NULL;
	return	head;
}

