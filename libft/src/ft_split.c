/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:06:08 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 11:57:48 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

static char	**split_alloc(const char *s, char c)
{
	size_t	wcount;

	if (s == NULL)
		return (NULL);
	wcount = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			while (*s == c)
				s++;
		}
		else if (*s != '\0')
		{
			wcount++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (ft_calloc(wcount + 1, sizeof(char *)));
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	wlen;
	size_t	w;

	split = split_alloc(s, c);
	if (split == NULL)
		return (NULL);
	w = 0;
	while (*s)
	{
		wlen = 0;
		while (*s != c && *s)
		{
			wlen++;
			s++;
		}
		split[w] = ft_substr(s - wlen, 0, wlen);
		if (wlen && !split[w++])
			return (free_split(split));
		while (*s == c && *s)
			s++;
	}
	split[w] = NULL;
	return (split);
}
