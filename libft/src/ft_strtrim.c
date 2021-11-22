/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:35:56 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/21 12:20:40 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimlen(const char *str, const char *set, int slen, int at_end)
{
	int		n;

	n = 0;
	if (!at_end)
		while (n < slen && ft_strchr(set, *str++))
			n++;
	else
	{
		while (*str)
			str++;
		while (n < slen && ft_strchr(set, *--str))
			n++;
	}
	return (n);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		slen;
	int		atrlen;
	int		ztrlen;

	if (!s1 || !set)
		return (NULL);
	slen = ft_strlen(s1);
	if (!slen)
		return (ft_calloc(1, sizeof(char)));
	ztrlen = trimlen(s1, set, slen, 1);
	if (ztrlen == slen)
		atrlen = 0;
	else
		atrlen = trimlen(s1, set, slen, 0);
	if (!atrlen && !ztrlen)
		return (ft_strdup(s1));
	return (ft_substr(s1, atrlen, slen - atrlen - ztrlen));
}
