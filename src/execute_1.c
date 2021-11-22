/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:55:00 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/02 16:07:38 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_and_update_last_exit(t_cmd **cmds, int size)
{
	int	wstatus;
	int	i;

	i = 0;
	while (i < size)
	{
		if (cmds[i]->pid != -1)
		{
			waitpid(cmds[i]->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_minish.last_exit = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
			{
				g_minish.last_exit = 128 + WTERMSIG(wstatus);
				if (g_minish.last_exit == 131 && i == size - 1)
					ft_putstr_fd("Quit", 2);
				ft_putchar_fd('\n', 1);
				break ;
			}
		}
		i++;
	}
	while (i < size)
		kill(cmds[i++]->pid, SIGINT);
}

static int	execsh(t_cmd *cmd)
{
	if (search_exec_file(cmd->argv) != 0)
	{
		sh_error(cmd->argv[0], NULL, "Command not found", 0);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->argv[0], cmd->argv, g_minish.env);
	sh_error(cmd->argv[0], NULL, NULL, 0);
	exit(126 + (errno == ENOENT));
}

static int	simple_command(t_cmd *cmd)
{
	dup2(cmd->io_fd[0], STDIN_FILENO);
	dup2(cmd->io_fd[1], STDOUT_FILENO);
	close(cmd->io_fd[0]);
	close(cmd->io_fd[1]);
	if (cmd->argv == NULL || *cmd->argv == NULL)
		return (g_minish.last_exit);
	if (check_if_builtin(cmd->argv))
		return (g_minish.last_exit);
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("error: fork");
	else if (cmd->pid == 0)
		execsh(cmd);
	else
		wait_and_update_last_exit(&cmd, 1);
	return (g_minish.last_exit);
}

static int	multi_pipe(t_cmd *cmd, bool piped)
{
	static int	in_fd = -1;
	int			rw_fd[2];

	if (pipe(rw_fd) == -1)
		return (EXIT_FAILURE);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("error: fork");
	else if (cmd->pid == 0)
	{
		close(rw_fd[0]);
		if (piped == true)
			dup2(rw_fd[1], STDOUT_FILENO);
		exit(simple_command(cmd));
	}
	close(rw_fd[1]);
	if (piped == false)
	{
		close(rw_fd[0]);
		rw_fd[0] = -1;
	}
	in_fd = rw_fd[0];
	return (EXIT_SUCCESS);
}

int	execute_cmds(t_cmd **cmds)
{
	int	stdio_fd[2];
	int	i;

	if (cmds == NULL)
		return (EXIT_FAILURE);
	stdio_fd[0] = dup(STDIN_FILENO);
	stdio_fd[1] = dup(STDOUT_FILENO);
	check_io_redirection(cmds);
	i = 0;
	if (cmds[i + 1] == NULL)
		simple_command(cmds[i]);
	else
	{
		while (cmds[i] != NULL)
		{
			multi_pipe(cmds[i], cmds[i + 1] != NULL);
			i++;
		}
		wait_and_update_last_exit(cmds, i);
	}
	dup2(stdio_fd[0], STDIN_FILENO);
	dup2(stdio_fd[1], STDOUT_FILENO);
	close(stdio_fd[0]);
	close(stdio_fd[1]);
	return (EXIT_SUCCESS);
}
