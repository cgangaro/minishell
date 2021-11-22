/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjimenez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:54:09 by wjimenez          #+#    #+#             */
/*   Updated: 2021/01/21 11:59:00 by wjimenez         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*uns_s1;
	unsigned char	*uns_s2;

	uns_s1 = (unsigned char *)s1;
	uns_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*uns_s1 != *uns_s2 || !*uns_s1 || !*uns_s2)
			return (*uns_s1 - *uns_s2);
		uns_s1++;
		uns_s2++;
	}
	return (0);
}
