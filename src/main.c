/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:45:14 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:45:16 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_clean(void)
{
	strarr_free(g_minish.env);
	rl_clear_history();
}

static void	minishell_loop(void)
{
	char	*line;
	t_cmd	**cmds;

	while (g_minish.end_sh == false)
	{
		signal(SIGINT, rl_sighandler);
		line = readline(CAWISH_PROMPT);
		if (line == NULL)
			g_minish.end_sh = true;
		else if (*line != '\0')
		{
			signal(SIGINT, SIG_IGN);
			add_history(line);
			cmds = parse_shell_line(&line);
			execute_cmds(cmds);
			cmds_free(cmds);
		}
		free(line);
	}
	ft_putendl_fd("exit", 2);
}

static void	minishell_init(void)
{
	extern char	**environ;
	int			i;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (environ[i] != NULL)
		i++;
	g_minish.env = malloc(sizeof(char *) * (i + 1));
	if (g_minish.env == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (environ[i] != NULL)
	{
		g_minish.env[i] = ft_strdup(environ[i]);
		if (g_minish.env[i++] == NULL)
		{
			strarr_free(g_minish.env);
			exit(EXIT_FAILURE);
		}
	}
	g_minish.env[i] = NULL;
	g_minish.last_exit = 0;
	g_minish.end_sh = false;
	increment_shlvl();
}

int	main(void)
{
	minishell_init();
	minishell_loop();
	minishell_clean();
	return (g_minish.last_exit);
}
