/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:42:23 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:44:14 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "libft.h"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdbool.h>
# include <sys/types.h>
# include <limits.h>

# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define CAWISH_PROMPT	"\001\033[91m\002cawish \001\033[33m\002&\001\033[0m\002 "
# define METACHAR		" \t\n|&;()<>"
# define IFS_DFL		" \t\n"

typedef struct s_minish
{
	char	**env;
	int		last_exit;
	bool	end_sh;
}			t_minish;

t_minish	g_minish;

typedef struct s_cmd
{
	char	**argv;
	char	**in;
	char	**out;
	int		io_fd[2];
	pid_t	pid;
}			t_cmd;

/*
** CORE FUNCTIONS
*/

t_cmd		**parse_shell_line(char **line);
void		parse_shell_param_expansion(char **line_ptr, char *map);
t_cmd		**parse_shell_tokens_into_cmds(char *line, char *map);

char		*open_heredoc(char *delimiter);
int			check_io_redirection(t_cmd **cmds);

int			execute_cmds(t_cmd **cmds);
int			check_if_builtin(char **argv);
int			search_exec_file(char **argv);

int			builtin_echo(char **cmd);
int			builtin_cd(char *path);
int			builtin_pwd(void);
int			builtin_env(bool put_also_novalue);
int			builtin_export(char **argv);
int			builtin_unset(char **names);
int			builtin_exit(char **argv);

/*
** UTILS FUNCTIONS
*/

int			increment_shlvl(void);
void		rl_sighandler(int signum);
int			sh_error(char *s1, char *s2, char *err, int type);

t_cmd		*cmd_new(void);
t_cmd		**cmds_new(char *line);
void		*cmds_free(t_cmd **cmds);

char		*ft_getenv(const char *name);
int			ft_setenv(const char *name, const char *value, int overwrite);
size_t		starts_with_valid_identifier(const char *string);

char		**strarr_add(char **arr, char *new);
void		strarr_del_at(char **arr, size_t i);
void		strarr_free(char **arr);

/*
** DEBUG FUNCTIONS
*/

int			put_mapping_result(char *line, char *map);
int			put_parsing_result(char *line, t_cmd **cmds);

#endif
