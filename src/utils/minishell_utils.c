/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:47:50 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:47:52 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

int	increment_shlvl(void)
{
	char	*old_shlvl_str;
	char	*new_shlvl_str;
	int		shlvl;

	old_shlvl_str = ft_getenv("SHLVL");
	if (old_shlvl_str == NULL)
		return (EXIT_FAILURE);
	shlvl = ft_atoi(old_shlvl_str);
	shlvl++;
	new_shlvl_str = ft_itoa(shlvl);
	if (new_shlvl_str == NULL)
		return (EXIT_FAILURE);
	ft_setenv("SHLVL", new_shlvl_str, true);
	free(new_shlvl_str);
	return (EXIT_SUCCESS);
}

/*
**
*/

void	rl_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_minish.last_exit = 128 + signum;
}

/*
**
*/

int	sh_error(char *s1, char *s2, char *err, int type)
{
	ft_putstr_fd("cavish: ", 2);
	if (type == 0)
	{
		ft_putstr_fd(s1, 2);
		if (s1 != NULL)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
		if (s2 != NULL)
			ft_putstr_fd(": ", 2);
		if (err == NULL)
			perror(NULL);
		else
			ft_putendl_fd(err, 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(err, 2);
	if (type == 2)
		ft_putstr_fd(", wanted", 2);
	ft_putstr_fd(" `", 2);
	if (type == 1)
		ft_putchar_fd(*s1, 2);
	else
		ft_putstr_fd(s1, 2);
	ft_putendl_fd("\'", 2);
	return (EXIT_FAILURE);
}

/*
** DEBUG FUNCTIONS
*/

int	put_mapping_result(char *line, char *map)
{
	if (line == NULL || map == NULL)
		return (EXIT_FAILURE);
	printf("=========================================================\n");
	printf("# LINE: |%s|\n", line);
	printf("---------------------------------------------------------\n");
	printf("↪ map:  |%s|\n", map);
	printf("=========================================================\n");
	return (EXIT_SUCCESS);
}

int	put_parsing_result(char *line, t_cmd **cmds)
{
	int	i;

	if (line == NULL || cmds == NULL)
		return (EXIT_FAILURE);
	printf("=========================================================\n");
	printf("# LINE: |%s|", line);
	while (*cmds != NULL)
	{
		printf("\n---------------------------------------------------------\n");
		i = 0;
		printf("• argv:");
		while ((*cmds)->argv[i] != NULL)
			printf(" |%s|", (*cmds)->argv[i++]);
		i = 0;
		printf("\n• in:  ");
		while ((*cmds)->in[i] != NULL)
			printf(" |%s|", (*cmds)->in[i++]);
		i = 0;
		printf("\n• out: ");
		while ((*cmds)->out[i] != NULL)
			printf(" |%s|", (*cmds)->out[i++]);
		cmds++;
	}
	printf("\n=========================================================\n");
	return (EXIT_SUCCESS);
}
