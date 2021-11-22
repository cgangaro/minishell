/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:45:41 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 16:05:07 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**
*/

static void	expand_param_update_map(char *from, char *to, char *map)
{
	int		from_line_len;
	int		to_line_len;
	int		from_param_len;
	int		to_param_len;
	char	c;

	from_line_len = ft_strlen(from);
	to_line_len = ft_strlen(to);
	if (ft_strncmp(from, "$?", 2) == 0)
		from_param_len = 2;
	else
		from_param_len = starts_with_valid_identifier(from + 1) + 1;
	to_param_len = to_line_len - from_line_len + from_param_len;
	if (*map == 'Q')
		c = 'Q';
	else
		c = 'e';
	ft_memmove(map + to_param_len, map + from_param_len, from_line_len + 1);
	ft_memset(map, c, to_param_len);
}

/*
**
*/

static char	*expand_to_last_exit(char *s, int pos)
{
	char	*expanded;
	char	*last_exit_str;
	int		last_exit_len;

	last_exit_str = ft_itoa(g_minish.last_exit);
	last_exit_len = 0;
	if (last_exit_str == NULL)
		perror("error: ft_itoa");
	else
		last_exit_len = ft_strlen(last_exit_str);
	expanded = malloc(sizeof(char) * ft_strlen(s) + last_exit_len - 1);
	if (expanded == NULL)
		perror("error: malloc");
	ft_strlcpy(expanded, s, pos + 1);
	ft_strlcpy(expanded + pos, last_exit_str, last_exit_len + 1);
	ft_strlcpy(expanded + pos + last_exit_len, s + pos + 2, -1);
	free(last_exit_str);
	return (expanded);
}

/*
**
*/

static char	*expand_to_var_value(char *s, int pos)
{
	char	*expanded;
	char	*name;
	char	*value;
	int		name_len;
	int		value_len;

	name_len = starts_with_valid_identifier(s + pos + 1);
	if (name_len == 0)
		return (NULL);
	name = ft_substr(s, pos + 1, name_len);
	if (name == NULL)
		perror("error: ft_substr");
	value = ft_getenv(name);
	free(name);
	value_len = 0;
	if (value != NULL)
		value_len = ft_strlen(value);
	expanded = malloc(sizeof(char) * (ft_strlen(s) + value_len - name_len));
	if (expanded == NULL)
		perror("error: malloc");
	ft_strlcpy(expanded, s, pos + 1);
	ft_strlcpy(expanded + pos, value, value_len + 1);
	ft_strlcpy(expanded + pos + value_len, s + pos + 1 + name_len, -1);
	return (expanded);
}

/*
** Will look for variables sybolized by a startig '$' in a string
** and try to expand them (effectively replacing the whole string)
** to their value. If the variable doesn't exist, cut it out from
** the string (including the starting '$'). The special case of
** "$?" will expand to the return value of last executed command
*/

void	parse_shell_param_expansion(char **line_ptr, char *map)
{
	char	*line;
	char	*expanded;
	int		i;

	line = *line_ptr;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && (map == NULL || map[i] != 'q'))
		{
			if (line[i + 1] == '?')
				expanded = expand_to_last_exit(line, i);
			else
				expanded = expand_to_var_value(line, i);
			if (expanded != NULL)
			{
				if (map != NULL)
					expand_param_update_map(line + i, expanded + i, map + i);
				free(line);
				line = expanded;
				*line_ptr = expanded;
			}
		}
		i++;
	}
}
