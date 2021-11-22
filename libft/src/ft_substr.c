/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:53:50 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/21 12:21:07 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	sublen;
	size_t	i;

	if (!s)
		return (NULL);
	sublen = ft_strlen(s);
	if (start >= sublen)
		sublen = 0;
	else if (sublen - start <= len)
		sublen -= start;
	else
		sublen = len;
	sub = malloc((sublen + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
