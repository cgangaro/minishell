/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:46:01 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:46:03 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc(int fd, char *delimiter)
{
	char	*line;
	int		r;

	r = EXIT_SUCCESS;
	if (fd == -1)
		return (EXIT_FAILURE);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			sh_error(delimiter, NULL, "Heredoc delimited by EOF", 2);
			r = EXIT_FAILURE;
			break ;
		}
		parse_shell_param_expansion(&line, NULL);
		if (ft_strncmp(line, delimiter, -1) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	return (r);
}

char	*open_heredoc(char *delimiter)
{
	static int	id = 0;
	char		*id_str;
	char		path[32];
	int			fd;
	int			wstatus;

	if (delimiter == NULL)
		return (NULL);
	ft_strlcpy(path, ".tmp/tmp-cawish-heredoc-", 25);
	id_str = ft_itoa(id++);
	ft_strlcpy(path + 24, id_str, 8);
	free(id_str);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fork() == 0)
		exit(write_heredoc(fd, delimiter));
	else if (wait(&wstatus) != -1 && WIFSIGNALED(wstatus))
	{
		g_minish.last_exit = 128 + WTERMSIG(wstatus);
		ft_putchar_fd('\n', 1);
		return (NULL);
	}
	close(fd);
	return (ft_strdup(path));
}

static int	output_redirection(t_cmd *cmd)
{
	char	*path;
	bool	append;
	int		i;

	i = 0;
	while (cmd->out[i] != NULL)
	{
		close(cmd->io_fd[1]);
		path = cmd->out[i] + 1;
		append = (*cmd->out[i] == '1');
		if (append == false)
			cmd->io_fd[1] = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			cmd->io_fd[1] = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->io_fd[1] == -1)
		{
			sh_error(path, NULL, NULL, 0);
			strarr_free(cmd->argv);
			cmd->argv = NULL;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	input_redirection(t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (cmd->in[i] != NULL)
	{
		close(cmd->io_fd[0]);
		path = cmd->in[i] + 1;
		cmd->io_fd[0] = open(path, O_RDONLY);
		if (cmd->io_fd[0] == -1)
		{
			sh_error(path, NULL, NULL, 0);
			strarr_free(cmd->argv);
			cmd->argv = NULL;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_io_redirection(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
	{
		if (input_redirection(cmds[i]) == 0)
			output_redirection(cmds[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
