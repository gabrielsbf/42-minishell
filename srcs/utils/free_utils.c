#include "../../includes/minishell.h"

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while ((*env))
	{
		temp = (*env);
		free((*env)->value);
		free((*env)->name);
		(*env)->value = NULL;
		(*env)->name = NULL;
		(*env)->head = NULL;
		(*env) = (*env)->next;
		free(temp);
	}
}

void	free_str(char **str)
{
	// printf("\n--------FREE STRING--------\n");
	// printf("address: %p is being deallocated\n", (*str));
	if ((str) == NULL || (*str) == NULL)
		return ;
	// printf("string is: %s\n", *str);
	free((*str));
	(*str) = NULL;
	// printf("confirm null: %s\n", *str);
	// printf("--------END OF FREE--------\n\n");
}

void	free_str_arr(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args && args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}

void	free_parser_str(t_parse **parser)
{
	if ((*parser)->command_text)
		free((*parser)->command_text);
	if ((*parser)->entire_text)
		free((*parser)->entire_text);
	if ((*parser)->main_command)
		free((*parser)->main_command);
	if ((*parser)->special_char)
		free((*parser)->special_char);
}

void	free_parser(t_parse **parser)
{
	t_parse	**temp;

	temp = NULL;
	if (!(*parser))
		return ;
	while ((*parser))
	{
		temp = parser;
		free_str_arr((*parser)->arguments);
		free_str_arr((*parser)->env_path);
		free_str_arr((*parser)->exec_txt);
		free_str_arr((*parser)->redir);
		free_parser_str(parser);
		(*parser)->head = NULL;
		(*parser) = (*parser)->next;
		free(*temp);
	}
}
