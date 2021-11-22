/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:47:35 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:47:36 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("error: cmd_new: ft_calloc : cmd");
		return (NULL);
	}
	cmd->argv = ft_calloc(1, sizeof(char *));
	cmd->in = ft_calloc(1, sizeof(char *));
	cmd->out = ft_calloc(1, sizeof(char *));
	cmd->io_fd[0] = -1;
	cmd->io_fd[1] = -1;
	cmd->pid = -1;
	if (cmd->argv != NULL && cmd->in != NULL && cmd->out != NULL)
		return (cmd);
	perror("error: cmd_new: ft_calloc: cmd->...");
	free(cmd->argv);
	free(cmd->in);
	free(cmd->out);
	free(cmd);
	return (NULL);
}

t_cmd	**cmds_new(char *line)
{
	t_cmd	**cmds;
	int		size;

	size = 1;
	while (*line != '\0')
		if (*line++ == '|')
			size++;
	cmds = ft_calloc(size + 1, sizeof(t_cmd *));
	if (cmds == NULL)
		perror("error: cmds_new: ft_calloc");
	return (cmds);
}

void	*cmds_free(t_cmd **cmds)
{
	int	i;

	if (cmds != NULL)
	{
		i = 0;
		while (cmds[i] != NULL)
		{
			strarr_free(cmds[i]->argv);
			strarr_free(cmds[i]->in);
			strarr_free(cmds[i]->out);
			free(cmds[i]);
			i++;
		}
		free(cmds);
	}
	return (NULL);
}
