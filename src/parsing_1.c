/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:45:36 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:45:38 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

static void	parse_shell_quote_removal(char *line, char *map)
{
	int	shift;
	int	i;

	shift = -1;
	i = 0;
	while (line[i] != '\0')
	{
		if (map[i] == '(' || map[i] == ')')
			shift = 0;
		else if (i != 0)
		{
			if (map[i - 1] == '0' && ft_strchr("_eQq", map[i]) != NULL)
				shift = 1;
			else if (ft_strchr("_eQq", map[i - 1]) != NULL && map[i] == '0')
				shift = 0;
		}
		if (shift != -1)
		{
			ft_strcpy(line + i - shift, line + i + !shift);
			ft_strcpy(map + i - shift, map + i + !shift);
			shift = -1;
		}
		else
			i++;
	}
}

/*
**
*/

static void	parse_shell_null_args(char *line, char *map)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (map[i] == '(' && map[i + 1] == ')')
		{
			ft_strcpy(line + i, line + i + 1);
			ft_strcpy(map + i, map + i + 1);
			line[i] = ' ';
			map[i] = '0';
		}
		if (i != 0
			&& ((map[i - 1] == '0' && map[i] == '0')
				|| (map[i - 1] == '0' && ft_strchr("ebQq", map[i]) != NULL)
				|| (ft_strchr("ebQq", map[i - 1]) != NULL && map[i] == '0')))
		{
			if (map[i - 1] != '0')
				i++;
			ft_strcpy(line + i - 1, line + i);
			ft_strcpy(map + i - 1, map + i);
			i--;
		}
		i++;
	}
}

/*
**
*/

static void	parse_shell_word_splitting(char *line, char *map)
{
	char	*env_ifs;

	env_ifs = ft_getenv("IFS");
	while (*line != '\0')
	{
		if (*map == 'e')
		{
			if (env_ifs != NULL)
			{
				if (ft_strchr(env_ifs, *line) != NULL)
				{
					if (ft_strchr(IFS_DFL, *line) != NULL)
						*map = 'b';
					*map = 's';
				}
			}
			else if (ft_strchr(IFS_DFL, *line) != NULL)
				*map = 'b';
		}
		line++;
		map++;
	}
}

/*
**
*/

static void	parse_shell_quotes(char *line, char *map)
{
	char	*quotes;
	int		len;
	char	c;

	while (*line != '\0')
	{
		if (ft_strchr("\"\'", *line) != NULL)
		{
			quotes = ft_strchr(line + 1, *line);
			if (quotes != NULL)
			{
				len = quotes - line;
				c = 'Q';
				if (*quotes == '\'')
					c = 'q';
				ft_memset(map, c, len);
				*map = '(';
				line += len;
				map += len;
				*map = ')';
			}
		}
		line++;
		map++;
	}
}

/*
**
*/

t_cmd	**parse_shell_line(char **line_ptr)
{
	char	map[LINE_MAX];
	char	*line;
	int		i;

	ft_memset(map, '_', LINE_MAX);
	map[ft_strlen(*line_ptr)] = '\0';
	parse_shell_quotes(*line_ptr, map);
	parse_shell_param_expansion(line_ptr, map);
	parse_shell_word_splitting(*line_ptr, map);
	parse_shell_null_args(*line_ptr, map);
	line = *line_ptr;
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("ebs(Qq)0", map[i]) == NULL)
		{
			if (line[i] == '|' || line[i] == '<' || line[i] == '>')
				map[i] = 'o';
			else if (line[i] == ' ' || line[i] == '\t')
				map[i] = ' ';
		}
		i++;
	}
	parse_shell_quote_removal(line, map);
	return (parse_shell_tokens_into_cmds(line, map));
}
