/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:05:18 by gabrfern          #+#    #+#             */
/*   Updated: 2024/11/18 01:05:19 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_dir(t_parse **parser, t_env **env, char *file)
{
	int		is_dir;

	if (check_slash((*parser)->main_command) == 1)
	{
		file = remove_slash(file);
		is_dir = ft_is_dir(file);
		printf("file -> %s\n", file);
		printf("is_dir -> %d\n", is_dir);
		free_str(&file);
		free_env(env);
		free_parser(parser);
		if (is_dir == 1 || is_dir == 0)
		{
			if (is_dir == 1)
				ft_putendl_fd("Is a directory", 2);
			if (is_dir == 0)
				ft_putendl_fd("Not a directory", 2);
			exit (126);
		}
		exit (127);
	}
}

char	*temp_pwd_wsl(char *temp)
{
	int		i;
	int		tempi;
	char	*path = "/home/bkwamme/";
	char	*pwd;

	tempi = 0;
	i = 0;
	while (i != 3)
	{
		if (temp[tempi] == '/')
			i++;
		tempi++;
	}
	pwd = ft_strjoin(path, &temp[tempi]);
	return (pwd);
}

char	*temp_actual_path_wsl(t_parse **parser, t_env **env)
{
	char	*file;
	char	*temp;
	char	*actual_path;
	char	cwd[4097];

	if ((*parser)->main_command[0] != '/')
	{
		temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), "/");
		file = temp_pwd_wsl(temp);
		free_str(&temp);
		actual_path = ft_strjoin(file, (*parser)->main_command);
		free_str(&file);
	}
	else
		actual_path = ft_strdup((*parser)->main_command);
	check_dir(parser, env, actual_path);
	if (ft_is_dir(actual_path) == 1)
	{
		free_parser(parser);
		free_env(env);
		free_str(&actual_path);
		ft_putendl_fd("Is a directory", 2);
		exit(126);
	}
	return (actual_path);
}

char	*actual_path(t_parse **parser, t_env **env)
{
	char	*file;
	char	*temp;
	char	cwd[4097];

	temp = ft_strjoin(getcwd(cwd, sizeof(cwd)), "/");
	file = ft_strjoin(temp, (*parser)->main_command);
	free_str(&temp);
	check_dir(parser, env, file);
	if (ft_is_dir(file) == 1)
	{
		free_parser(parser);
		free_env(env);
		free_str(&file);
		ft_putendl_fd("Is a directory", 2);
		exit(126);
	}
	return (file);
}

void	execution(t_parse **parser, t_env **env, char **envp)
{
	char	*path;

	(void)env;
	path = NULL;
	if (ft_strcmp((*parser)->main_command, ".") == 0)
	{
		free_parser(parser);
		free_env(env);
		exit (2);
	}
	create_execargs(parser);
	if (ft_strncmp((*parser)->main_command, "./", 2) == 0
		|| ft_strncmp((*parser)->main_command, "../", 3) == 0
		|| check_slash((*parser)->main_command) == 1)
		path = temp_actual_path_wsl(parser, env);
	else
		path = create_path_exec(parser);
	if (access((*parser)->main_command, F_OK | X_OK) == 0)
		execve((*parser)->main_command, (*parser)->exec_txt, envp);
	if (!path)
	{
		free_parser(parser);
		free_env(env);
		exit (127);
	}
	execve(path, (*parser)->exec_txt, envp);
}
