/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:05:40 by cgangaro          #+#    #+#             */
/*   Updated: 2021/10/28 10:04:59 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** > BUILTINs
**
** - echo (with -n option)
** - cd
** - pwd
** - export
** - unset
** - env
** - exit
*/

int	check_if_builtin(char **argv)
{
	int	r;

	r = 1;
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		g_minish.last_exit = builtin_echo(&argv[1]);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		g_minish.last_exit = builtin_cd(argv[1]);
	else if (ft_strncmp(argv[0], "pwd", 4) == 0)
		g_minish.last_exit = builtin_pwd();
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		g_minish.last_exit = builtin_export(&argv[1]);
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		g_minish.last_exit = builtin_unset(&argv[1]);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		g_minish.last_exit = builtin_env(false);
	else if (ft_strncmp(argv[0], "exit", 5) == 0)
		g_minish.last_exit = builtin_exit(&argv[1]);
	else
		r = 0;
	return (r);
}

/*
** Concatenates two strings into one representing a path
** and then copy it at provided destination. The pointer
** dst needs to be mallocated before hand with enough space
** and therefore should obviously be freed at some point.
*/

static char	*cpy_joinpath(char *dst, const char *path1, const char *path2)
{
	int	len1;

	len1 = ft_strlen(path1);
	ft_strlcpy(dst, path1, len1 + 1);
	if (dst[len1 - 1] != '/')
		dst[len1++] = '/';
	ft_strlcpy(&dst[len1], path2, PATH_MAX - len1);
	return (dst);
}

static bool	is_executable(char *path)
{
	struct stat	file_status;

	if (lstat(path, &file_status) == 0 && file_status.st_mode & S_IFREG)
	{
		if (!(file_status.st_mode & S_IXUSR))
			g_minish.last_exit = 126;
		return (true);
	}
	return (false);
}

static char	**search_exec_paths_if_not_local(char **argv)
{
	char	**env_paths;
	char	*env_path;

	if (ft_strchr(argv[0], '/') != NULL)
		return (NULL);
	env_path = ft_getenv("PATH");
	if (env_path == NULL)
		return (NULL);
	env_paths = ft_split(env_path, ':');
	if (env_paths == NULL)
		return (NULL);
	if (*env_paths == NULL)
	{
		strarr_free(env_paths);
		return (NULL);
	}
	return (env_paths);
}

int	search_exec_file(char **argv)
{
	char	exec_path[PATH_MAX];
	char	**env_paths;
	char	*tmp;
	int		i;

	env_paths = search_exec_paths_if_not_local(argv);
	if (env_paths == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (env_paths[i] != NULL
		&& cpy_joinpath(exec_path, env_paths[i], argv[0])
		&& is_executable(exec_path) == false)
		i++;
	if (env_paths[i] != NULL)
	{
		strarr_free(env_paths);
		tmp = ft_strdup(exec_path);
		if (tmp == NULL)
			return (EXIT_FAILURE);
		free(argv[0]);
		argv[0] = tmp;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
