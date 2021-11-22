/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:55:43 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 11:45:06 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	u;

	if (dst == src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	u = (unsigned char)c;
	while (n--)
	{
		*d++ = *s++;
		if (*(s - 1) == u)
			return (d);
	}
	return (NULL);
}
