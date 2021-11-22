/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:25:42 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/19 11:45:29 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*u;

	u = (unsigned char *)str;
	while (n--)
	{
		if (*u == (unsigned char)c)
			return (u);
		u++;
	}
	return (NULL);
}
