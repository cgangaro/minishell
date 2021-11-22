/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <wjimenez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:47:42 by wjimenez          #+#    #+#             */
/*   Updated: 2021/11/10 10:47:43 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	int	name_len;
	int	i;

	if (name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (g_minish.env[i] != NULL)
	{
		if (ft_strncmp(g_minish.env[i], name, name_len) == 0
			&& g_minish.env[i][name_len] == '=')
			return (g_minish.env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

static int	expand_add_env(char *add)
{
	char	**env_expanded;
	int		i;

	i = 0;
	while (g_minish.env[i] != NULL)
		i++;
	env_expanded = malloc(sizeof(char *) * (i + 2));
	if (env_expanded == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (g_minish.env[i] != NULL)
	{
		env_expanded[i] = g_minish.env[i];
		i++;
	}
	env_expanded[i++] = add;
	env_expanded[i] = NULL;
	free(g_minish.env);
	g_minish.env = env_expanded;
	return (EXIT_SUCCESS);
}

static char	*get_env_var_str(const char *name, const char *value)
{
	char	*env_var;
	int		env_var_len;
	int		name_len;
	int		value_len;
	bool	has_value;

	name_len = ft_strlen(name);
	value_len = 0;
	has_value = (value != NULL);
	if (has_value == true)
		value_len = ft_strlen(value);
	env_var_len = name_len + has_value + value_len;
	env_var = malloc(sizeof(char) * (env_var_len + 1));
	if (env_var == NULL)
		return (NULL);
	ft_strlcpy(env_var, name, name_len + 1);
	if (has_value)
		env_var[name_len] = '=';
	ft_strlcpy(&env_var[name_len + has_value], value, value_len + 1);
	return (env_var);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	char	*env_var;
	int		name_len;
	int		i;

	env_var = get_env_var_str(name, value);
	if (env_var == NULL)
	{
		perror("error: ft_setenv: get_env_var_str");
		return (EXIT_FAILURE);
	}
	name_len = ft_strlen(name);
	i = 0;
	while (g_minish.env[i] != NULL
		&& !(!ft_strncmp(g_minish.env[i], name, name_len)
			&& (g_minish.env[i][name_len] == '='
			|| g_minish.env[i][name_len] == '\0')))
		i++;
	if (g_minish.env[i] != NULL && overwrite)
	{
		free(g_minish.env[i]);
		g_minish.env[i] = env_var;
	}
	else
		expand_add_env(env_var);
	return (EXIT_SUCCESS);
}

size_t	starts_with_valid_identifier(const char *string)
{
	size_t	identifier_len;

	identifier_len = 1;
	if (string == NULL || !(ft_isalpha(*string) || *string == '_'))
		return (0);
	string++;
	while (ft_isalnum(*string) || *string == '_')
	{
		identifier_len++;
		string++;
	}
	if (*string != '\0' && ft_strchr(".+{}-*#@!", *string) != NULL)
		return (0);
	return (identifier_len);
}
