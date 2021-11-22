/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:44:49 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:44:51 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **argv)
{
	char	*name;
	int		name_len;
	char	*value;
	int		r;

	r = EXIT_SUCCESS;
	if (*argv == NULL)
		return (builtin_env(true));
	while (*argv)
	{
		name_len = starts_with_valid_identifier(*argv);
		if (name_len != 0)
		{
			name = ft_substr(*argv, 0, name_len);
			value = NULL;
			if ((*argv)[name_len] == '=')
				value = *argv + name_len + 1;
			ft_setenv(name, value, 1);
			free(name);
		}
		else
			r = sh_error("export", *argv, "Not a valid identifier", 0);
		argv++;
	}
	return (r);
}

int	builtin_unset(char **names)
{
	int	name_len;
	int	i;
	int	r;

	r = EXIT_SUCCESS;
	while (*names != NULL)
	{
		name_len = starts_with_valid_identifier(*names);
		if (name_len != 0)
		{
			i = 0;
			while (g_minish.env[i])
			{
				if (ft_strncmp(g_minish.env[i], *names, name_len) == 0
					&& ((*names)[name_len] == '='
					|| (*names)[name_len] == '\0'))
					strarr_del_at(g_minish.env, i);
				i++;
			}
		}
		else
			r = sh_error("unset", *names, "Not a valid identifier", 0);
		names++;
	}
	return (r);
}

int	builtin_env(bool put_also_novalue)
{
	int	i;

	i = 0;
	while (g_minish.env[i])
	{
		if (put_also_novalue == true || ft_strchr(g_minish.env[i], '='))
		{
			if (put_also_novalue == true)
				ft_putstr_fd("export ", 1);
			ft_putendl_fd(g_minish.env[i], 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_exit(char **argv)
{
	int	i;

	g_minish.end_sh = true;
	if (argv != NULL && argv[0] != NULL)
	{
		i = (argv[0][0] == '-');
		while (argv[0][i])
		{
			if (ft_isdigit(argv[0][i]) == false)
			{
				sh_error("exit", argv[0], "Numeric argument required", 0);
				return (2);
			}
			i++;
		}
		g_minish.last_exit = (unsigned char)ft_atoi(*argv);
		if (argv[1] != NULL)
		{
			sh_error("exit", NULL, "Too many arguments", 0);
			g_minish.end_sh = false;
			return (1);
		}
	}
	return (g_minish.last_exit);
}
