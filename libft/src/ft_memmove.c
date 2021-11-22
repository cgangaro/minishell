/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:11:49 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 11:53:43 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	if (dst < src)
		while (n--)
			*d++ = *s++;
	else
	{
		d = d + (n - 1);
		s = s + (n - 1);
		while (n--)
			*d-- = *s--;
	}
	return (dst);
}
