/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:44:41 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:44:43 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	bool	n_option;
	int		i;

	n_option = false;
	while (*argv != NULL && **argv == '-')
	{
		i = 1;
		while ((*argv)[i] == 'n')
			i++;
		if ((*argv)[i] == '\0')
			n_option = true;
		else
			break ;
		argv++;
	}
	while (*argv != NULL)
	{
		ft_putstr_fd(*argv++, 1);
		if (*argv != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (n_option == false)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char *path)
{
	char	dir_abspath[PATH_MAX];
	bool	put_dir_abspath;

	put_dir_abspath = false;
	if (path == NULL)
		path = ft_getenv("HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD");
		put_dir_abspath = true;
	}
	if (chdir(path) != 0)
		return (sh_error("cd", path, NULL, 0));
	getcwd(dir_abspath, PATH_MAX);
	ft_setenv("OLDPWD", ft_getenv("PWD"), true);
	ft_setenv("PWD", dir_abspath, true);
	if (put_dir_abspath == true)
		ft_putendl_fd(dir_abspath, 1);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(void)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(pwd, 1);
	return (EXIT_SUCCESS);
}
