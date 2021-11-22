/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:45:47 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:45:48 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** A word here is defined by a succession of characters delimited
** by whitespaces or a pair of quotes.
** The fuction finds the start and the end of the next word in string
** passed as parameter and returns a duplicate (meaning mallocated copy)
** of it (NULL if no word is found before the next metacharacter).
** The pointer is moved to the end of that word through the process.
*/

static char	*parse_shell_word(char **line_p, char **map_p, bool split)
{
	char	*word_start;
	char	*word_end;
	int		word_len;

	while (**map_p != '\0' && (**map_p == ' ' || **map_p == 'b'))
	{
		(*line_p)++;
		(*map_p)++;
	}
	if (**line_p == '\0' || **map_p == 'o')
		return (NULL);
	word_start = *line_p + (**map_p == '0');
	while (**map_p != '\0' && **map_p != ' ' && **map_p != 'o')
	{
		(*line_p)++;
		(*map_p)++;
		if ((**map_p == 'b' || **map_p == 's') && split == true)
			break ;
	}
	word_end = *line_p - (**map_p == '0');
	word_len = word_end - word_start;
	return (ft_substr(word_start, 0, word_len));
}

/*
**
*/

static int	parse_shell_redir_type(char **line_p, char **map_p)
{
	int	type;

	type = (**line_p == '>');
	if (**line_p == *(*line_p + 1))
		type += 2;
	(*line_p)++;
	(*map_p)++;
	if (type == 2 || type == 3)
	{
		(*line_p)++;
		(*map_p)++;
	}
	return (type);
}

/*
**
*/

static int	parse_shell_redir(char **line_p, char **map_p, t_cmd *cmd, int type)
{
	char	***redirection;
	char	*word;
	char	*heredoc_path;
	char	*file_path;

	if (type % 2 == 0)
		redirection = &cmd->in;
	else
		redirection = &cmd->out;
	word = parse_shell_word(line_p, map_p, false);
	if (type == 2)
	{
		heredoc_path = open_heredoc(word);
		free(word);
		word = heredoc_path;
	}
	if (word == NULL)
		return (EXIT_FAILURE);
	file_path = ft_strjoin("0", word);
	free(word);
	if (file_path == NULL)
		return (EXIT_FAILURE);
	*file_path += type / 2;
	*redirection = strarr_add(*redirection, file_path);
	return (redirection == NULL);
}

/*
**
*/

static int	parse_shell_cmd(char **line_p, char **map_p, t_cmd *cmd)
{
	char	*word;
	int		redir_type;

	while (**line_p != '\0')
	{
		word = parse_shell_word(line_p, map_p, true);
		if (word != NULL)
			cmd->argv = strarr_add(cmd->argv, word);
		else if (**line_p == '<' || **line_p == '>')
		{
			redir_type = parse_shell_redir_type(line_p, map_p);
			if (parse_shell_redir(line_p, map_p, cmd, redir_type) != 0)
				return (2);
		}
		else if (**line_p == '|')
			break ;
	}
	if (*cmd->argv == NULL && *cmd->in == NULL && *cmd->out == NULL)
		return (1);
	if (**line_p != '\0')
	{
		(*line_p)++;
		(*map_p)++;
	}
	return (EXIT_SUCCESS);
}

/*
** Goes through user line input, ignoring empty white space separating words
** and then parsing them accordingly to their nature.
** They can be part of an array of strings making a single command to execute
** XOR a redirection of its individual input/output (can be done several times)
** XOR the marker of a pipe (therefore starting the parsing of a new command)
*/

t_cmd	**parse_shell_tokens_into_cmds(char *line, char *map)
{
	t_cmd	**cmds;
	int		result;
	int		i;

	cmds = cmds_new(line);
	if (cmds == NULL)
		return (NULL);
	i = 0;
	while (*line != '\0')
	{
		cmds[i] = cmd_new();
		if (cmds[i] == NULL)
			return (cmds_free(cmds));
		result = parse_shell_cmd(&line, &map, cmds[i++]);
		if (result != 0)
		{
			if (*line == '|' || (result == 2 && g_minish.last_exit != 130))
			{
				sh_error(line, NULL, "Syntax error near unexpected token", 1);
				g_minish.last_exit = 2;
			}
			return (cmds_free(cmds));
		}
	}
	return (cmds);
}
